/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:30:41 by vmyshko           #+#    #+#             */
/*   Updated: 2024/08/26 12:04:52 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <stdlib.h> 
// #include <stdio.h>
// #include <string.h>
// #include <ctype.h>
// #include <stdbool.h>
// #include <errno.h>
#include "../../hell.h"

// NEW PWD
int	ft_pwd(t_env **head, t_hell *hell)
{
	t_env	*temp;
	char	*pwd;
	int		out;

	pwd = getcwd(NULL, 0);
	out = 1;
	if (hell->outfile)
		out = hell->outfile;
	if (pwd)
		ft_putendl_fd(pwd, out);
	else
	{
		temp = ft_search_in_list(head, "PWD");
		if (temp)
			ft_putendl_fd(temp->value, out);
	}
	free(pwd);
	return (0);
}

void	firethrower(int exitstat, t_hell *hell)
{
	t_env	*temp;

	temp = hell->env;
	gigaclose();
	delhere();
	(fth(hell, &hell->env), free_env(temp));
	exit(exitstat);
}

//first check if there is a pipe (hell->pipe)->  return 0 immediately
//(not perform an exit)-> the command is part of a pipeline.
// no args ->simple exit, args? numeric?multiple? -mistake
// convert 2 arg  to a long int (ft_atoi_long), casts it to 
// an unsigned char for the exit code, 
// and assign it to hell->exit.
// calls firethrower with the new exit code (hell->exit) to
// terminate the program.
int	my_exit(t_hell *hell)
{
	if (hell->pipe)
		return (0);
	if (hell->arguments[0] && !hell->arguments[1])
	{
		ft_putstr_fd("exit\n", 2);
		firethrower(hell->exit, hell);
	}
	if (!is_num(hell->arguments[1]))
	{
		ft_putstr_fd("hell: exit: ", 2);
		ft_putstr_fd(hell->arguments[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		firethrower(2, hell);
	}
	if (hell->arguments[2])
	{
		ft_putstr_fd("hell: exit: too many arguments\n", 2);
		return (1);
	}
	ft_putstr_fd("exit\n", 2);
	hell->exit = (unsigned char)ft_atoi_long(hell->arguments[1]);
	firethrower(hell->exit, hell);
	return (0);
}

// int my_exit(t_hell *hell) {
//     ft_putstr_fd("exit\n", 1);
// 	//if only 1 argument exit
//     if (hell->arguments[0] && !hell->arguments[1]) {
//         exit(hell->exit);
//     }
//     if (hell->arguments[2]) {
//         return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
//     }
//     if (!is_num(hell->arguments[1])) 
// 	// if (!is_digit(hell->arguments[1])) 
// 	{
//         return (ft_putstr_fd("minishell: exit: ", 2), 
//                        ft_putstr_fd(hell->arguments[1], 2),
//                 ft_putstr_fd(": numeric argument required\n", 2), 
//                                                exit(2), 2);
//     }
//     hell->exit = (unsigned char)ft_atoi_long(hell->arguments[1]);
//     exit(hell->exit);
// }
//TEST PWD
// void create_test_environment(t_env **head)
// {
//    
//     ft_delete_from_list(head, "VAR1"); // Ensure clean start
//     ft_delete_from_list(head, "VAR2"); // Ensure clean start
//     // Add some initial environment variables
//     *head = malloc(sizeof(t_env));
//     (*head)->key = strdup("VAR1");
//     (*head)->value = strdup("value1");
//     (*head)->next = malloc(sizeof(t_env));
//     (*head)->next->key = strdup("VAR2");
//     (*head)->next->value = strdup("value2");
//     (*head)->next->next = NULL;
// }
// int main()
// {
//     t_env *env_list = NULL;
//     t_hell test_hell;
//     // Create a test environment
//     create_test_environment(&env_list)
//     // Set up test arguments
//     char *test_arguments[] = {"VAR1", "VAR2", NULL};
//     test_hell.arguments = test_arguments;
//     // Print initial environment
//     printf("Initial environment:\n");
//     t_env *temp = env_list;
//     while (temp != NULL)
//     {
//         printf("%s=%s\n", temp->key, temp->value);
//         temp = temp->next;
//     }
//     // Call ft_unset
//     printf("\nUnsetting variables...\n");
//     int ret = ft_unset(&test_hell, &env_list);
//     if (ret != 0)
//     {
//         fprintf(stderr, "ft_unset returned an error\n");
//         return EXIT_FAILURE;
//     }
//     // Print updated environment
//     printf("\nUpdated environment:\n");
//     temp = env_list;
//     while (temp != NULL)
//     {
//         printf("%s=%s\n", temp->key, temp->value);
//         temp = temp->next;
//     }
//     // Free allocated memory (not shown in original ft_unset)
//     while (env_list != NULL)
//     {
//         temp = env_list;
//         env_list = env_list->next;
//         free(temp->key);
//         free(temp->value);
//         free(temp);
//     }
//     return EXIT_SUCCESS;
// }
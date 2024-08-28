/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:30:41 by vmyshko           #+#    #+#             */
/*   Updated: 2024/08/23 17:42:19 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hell.h"

// printing all environment variables, 
// too much args catch
//if outfile is not open, print to stdout
//if outfile is open, print to outfile and
// close file descriptor 
int	ft_env(t_hell *hell)
{
	t_env	*temp;
	int		out;

	if (hell == NULL || hell->env == NULL)
		return (ft_putstr_fd("Error: No env variables available\n", 2), 1);
	if (hell->arguments[1] != NULL)
		return (printf("env:'%s': No such file or directory\n",
				hell->arguments[1]), 1);
	temp = hell->env;
	out = hell->outfile;
	if (!out)
		out = 1;
	while (temp != NULL)
	{
		if (temp->value != NULL && temp->env)
		{
			ft_putstr_fd(temp->key, out);
			ft_putchar_fd('=', out);
			ft_putendl_fd(temp->value, out);
		}
		temp = temp->next;
	}
	if (hell->outfile > 2)
		close(out);
	return (0);
}

//Util for 2_linked_list
void	*handle_malloc_failure(const char *msg)
{
	perror(msg);
	return (NULL);
}

int	ft_count_list(t_env **head)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = *head;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

//Util for execution
// void	gigaclose(void)
// {
// 	DIR				*dir;
// 	struct dirent	*entry;
// 	int				fd;

// 	dir = opendir("/proc/self/fd");
// 	if (!dir)
// 		return ;
// 	entry = readdir(dir);
// 	while (entry != NULL)
// 	{
// 		fd = ft_atoi_long(entry->d_name);
// 		if (fd > STDERR_FILENO && fd < 1024)
// 		{
// 			if (close(fd) == -1)
// 				perror("close");
// 		}
// 		entry = readdir(dir);
// 	}
// 	closedir(dir);
// }

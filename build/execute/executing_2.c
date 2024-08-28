/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:18:11 by vmyshko           #+#    #+#             */
/*   Updated: 2024/08/23 17:36:00 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hell.h"

//creating and maintaining the additional "_" env variable
// that represents the last word in a line that had no pipes

//determine the last argument in the `hell->arguments` array and updates
// the env var "_" with this argument, provided that the command line does not
// contain any pipes (`|`). The "_" var  stores the last word of the most
// recent command line. If the command includes pipes or has no arguments,
// the "_" variable is not updated.
int	get_additionals(t_hell *hell)
{
	int	i;

	i = 0;
	while (hell && hell->arguments && hell->arguments[i])
		i++;
	if (hell->arguments[0])
		i--;
	if (hell && !hell->pipe && hell->arguments && hell->arguments[i])
		ft_add_or_replace(&(hell->env), "_", hell->arguments[i]);
	return (i);
}

// start the execution process, ft_is_builtins gets to execution no metter
// if it is actually a terminal command, it sets hell->exit to a negative number
// so if we see a negative number we know it is a pid of a child process
// in the end of the while loop "the_pid" = 0 (last command = builtin)
// or > 0, which equals to the pid of the last started child
int	ft_run_commands(t_hell *hell)
{
	t_hell	*temp;
	int		the_pid;

	temp = hell;
	the_pid = 0;
	while (temp)
	{
		if (temp->arguments && temp->arguments[0] != NULL && temp->run > 0)
			hell->exit = ft_is_builtins(temp, &temp->env);
		if (hell->exit < 0)
			the_pid = -hell->exit;
		else
			the_pid = 0;
		if (temp->next)
			temp = temp->next;
		else
			break ;
	}
	gigaclose();
	return (the_pid);
}

//returns the pid of a child (if existant) to the ft_execute
int	ft_execute_commands(t_hell *hell)
{
	get_additionals(hell);
	return (ft_run_commands(hell));
}

// while we wait for children we should ignore Ctrl+C (sigint)
// and after waiting is done it's set back to what we need
// then if "the_pid" != 0 we get the exit status of that last process
// and = 0 we grab the exit status from our env where the builtins put it
int	ft_execute_wait_and_finalize(t_hell *hell, int the_pid)
{
	int	i;
	int	final_exit;

	signal(SIGINT, SIG_IGN);
	i = waitpid(-1, &hell->exit, 0);
	while (i != -1)
	{
		if (i == the_pid)
			final_exit = hell->exit;
		i = waitpid(-1, &hell->exit, 0);
	}
	signal(SIGINT, handle_sigint);
	if (hell->run == 1 && the_pid && WIFEXITED(final_exit))
		final_exit = WEXITSTATUS(final_exit);
	else if (hell->run == 1 && the_pid && WIFSIGNALED(final_exit))
		final_exit = 128 + WTERMSIG(final_exit);
	else
		final_exit = ft_atoi_long(ft_search_in_list(&(hell->env), "?")->value);
	return (final_exit);
}

// gets the commands running, then waits for all of them and
// remembers the exit status of the last one
int	ft_execute(t_hell *hell)
{
	int	the_pid;
	int	final_exit;

	the_pid = ft_execute_commands(hell);
	final_exit = ft_execute_wait_and_finalize(hell, the_pid);
	return (final_exit);
}

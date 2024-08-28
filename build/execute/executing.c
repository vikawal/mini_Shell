/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:32:51 by vmyshko           #+#    #+#             */
/*   Updated: 2024/08/23 17:46:57 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hell.h"

//closes all the file descriptors except standart for current process
void	gigaclose(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				fd;

	dir = opendir("/proc/self/fd");
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry != NULL)
	{
		fd = ft_atoi_long(entry->d_name);
		if (fd > STDERR_FILENO && fd < 1024)
		{
			if (close(fd) == -1)
				perror("close");
		}
		entry = readdir(dir);
	}
	closedir(dir);
}

// Change the signal handlers to default for the child process
// Redirect  input/output file descriptors
// Replace the current process image with a new process image -EXECVE
void	ft_execve(t_hell *hell, t_env *env)
{
	char	**env_arr;
	int		i;

	env_arr = ft_list_to_arr(&env);
	(signal(SIGQUIT, SIG_DFL), signal(SIGINT, SIG_DFL));
	if (!env_arr)
		return (handle_error("ft_execve: ft_list_to_arr failed"));
	if (hell->infile)
		dup2(hell->infile, STDIN_FILENO);
	if (hell->outfile)
		dup2(hell->outfile, STDOUT_FILENO);
	gigaclose();
	execve(hell->path, hell->arguments, env_arr);
	if (env_arr)
	{
		i = 0;
		while (env_arr[i])
		{
			free(env_arr[i]);
			i++;
		}
		free(env_arr);
	}
	exit(1);
}

//fork a new process and execute a command in the child process (pid = 0),
//returns a negative pid of a child for getting the exitstatus later
int	ft_exec(t_hell *hell, t_env **head)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		return (ft_put_err("fork: ", "Fork failed", errno));
	else if (pid == 0)
		ft_execve(hell, *head);
	return (-pid);
}

//  checking if the executable file exists in a given path 
void	ft_exec_file(t_hell *hell, t_env **head, char *path, int *status)
{
	char	*full_path;

	full_path = ft_join_path(path, hell->arguments[0]);
	if (access(full_path, X_OK))
		return (free (full_path));
	if (*status == -77)
	{
		hell->path = ft_strdup(full_path);
		*status = ft_exec(hell, head);
	}
	free(full_path);
}

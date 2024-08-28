/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:44:17 by vmyshko           #+#    #+#             */
/*   Updated: 2024/08/23 17:20:12 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hell.h"

// If the path is a directory, -> error 126
//If the path is executable ->execute? permissions ->127?
//not? -> no such file? (ENOENT)

int	ft_file_check(t_hell *hell, t_env **head)
{
	DIR	*dir;

	dir = opendir(hell->arguments[0]);
	if (dir != NULL)
	{
		closedir(dir);
		ft_add_or_replace(head, "?", "126");
		return (ft_put_err(hell->arguments[0], ": Is a directory", 0));
	}
	if (errno != ENOENT)
	{
		if (access(hell->arguments[0], X_OK) != -1)
			return (ft_exec(hell, head));
		ft_add_or_replace(head, "?", "126");
		return (ft_put_err(hell->arguments[0], ": permission denied", 0));
	}
	ft_add_or_replace(head, "?", "127");
	return (ft_put_err(hell->arguments[0], ": No such file or directory", 0));
}

//path + command -> executable path
char	*ft_join_path(char *path, char *cmd)
{
	char	*path_tmp;
	char	*full_path;

	if (!path || !cmd)
		return (NULL);
	path_tmp = my_strjoin(path, "/");
	if (!path_tmp)
		return (NULL);
	full_path = my_strjoin(path_tmp, cmd);
	free(path_tmp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

// Splits the PATH string into an array of directory paths.
//Iterate over each directory to search for the executable.
//f the executable is found or executed successfully, it updates the status.

int	ft_find_file(t_hell *hell, t_env **head)
{
	t_env			*temp;
	char			**path;
	int				status;
	int				i;

	i = 0;
	status = -77;
	temp = ft_search_in_list(head, "PATH");
	if (temp == NULL)
		return (ft_put_err("", "no PATH", 2));
	path = ft_split(temp->value, ':');
	if (!path)
		return (ft_put_err("ft_split: ", "Failed to split PATH", 2));
	while (path[i] != NULL)
	{
		ft_exec_file(hell, head, path[i], &status);
		if (status != -77)
			break ;
		i++;
	}
	freeargs(&path);
	return (status);
}

//first argument contains a '/' character? -> direct path
//yes? -> check if the file exists and has execute permissions
// If NO '/',-> serach path in env
//If the command is not found -> 127

int	ft_check_path(t_hell *hell, t_env **head)
{
	int	status;

	if (ft_strchr(hell->arguments[0], '/'))
	{
		hell->path = ft_strdup(hell->arguments[0]);
		if (!hell->path)
			return (1);
		return (ft_file_check(hell, head));
	}
	else
	{
		status = ft_find_file(hell, head);
		if (status != -77)
			return (status);
		if (!hell->next)
			ft_add_or_replace(head, "?", "127");
		return (ft_put_err(hell->arguments[0], ": command not found", 0));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:40:20 by vmyshko           #+#    #+#             */
/*   Updated: 2024/08/26 12:05:08 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hell.h"

int	ft_replace_pwd(t_env **head)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (1);
	ft_replaceit(head, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}

static int	ft_file_check(char *check)
{
	DIR		*dir;
	char	*join;
	char	*error;

	dir = opendir(check);
	if (dir != NULL)
	{
		closedir(dir);
		return (0);
	}
	join = my_strjoin(": ", strerror(errno));
	error = my_strjoin(check, join);
	free(join);
	ft_put_err("cd: ", error, 1);
	free(error);
	return (1);
}

int	ft_change_dir(t_env **head, char *dir, t_hell *hell)
{
	t_env	*temp;
	int		check;

	check = 0;
	if (ft_file_check(dir))
		return (1);
	if (hell->pipe == 1)
		return (0);
	chdir(dir);
	temp = ft_search_in_list(head, "PWD");
	if (temp)
		ft_replaceit(head, "OLDPWD", temp->value);
	else
		ft_replaceit(head, "OLDPWD", NULL);
	return (ft_replace_pwd(head));
}
// change the way the pwd and oldpwd get changed

int	ft_handle_oldpwd(t_env **head, t_hell *hell)
{
	t_env	*temp;

	temp = ft_search_in_list(head, "OLDPWD");
	if (!temp)
		return (ft_put_err("cd:", " OLDPWD not set", 1));
	if (!hell->outfile)
		ft_putendl_fd(temp->value, 1);
	else
		ft_putendl_fd(temp->value, hell->outfile);
	return (0);
}

/**
 * - If no directory argument is provided, it changes to the `HOME` dir.
 * - If more than one argument is provided, -> error).
 * - If the argument is `"-"`, it changes to the  (`OLDPWD`).
 * - General:, it changes to the directory specified by the first arg
 * Return: 0 on successful directory change, 1 on error.
 */
int	ft_cd(t_hell *hell, t_env **head)
{
	char	*dir;
	t_env	*temp;

	if ((!hell || hell->arguments[1] == NULL))
	{
		temp = ft_search_in_list(head, "HOME");
		if (!temp)
			return (ft_put_err("cd:", " HOME not set", 1));
		dir = temp->value;
	}
	else if (hell->arguments[2] != NULL)
		return (ft_put_err("cd:", " too many arguments", 1));
	else if (!(ft_strcmp(hell->arguments[1], "-")))
	{
		if (ft_handle_oldpwd(head, hell) != 0)
			return (1);
		dir = ft_search_in_list(head, "OLDPWD")->value;
	}
	else
		dir = hell->arguments[1];
	return (ft_change_dir(head, dir, hell));
}

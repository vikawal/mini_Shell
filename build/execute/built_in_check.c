/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:48:33 by vmyshko           #+#    #+#             */
/*   Updated: 2024/08/23 15:11:47 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hell.h"

// #include <string.h>

#define ECHO_CMD "echo"
#define CD_CMD "cd"
#define PWD_CMD "pwd"
#define ENV_CMD "env"
#define EXPORT_CMD "export"
#define UNSET_CMD "unset"
#define EXIT_CMD "exit"

static t_builtin	get_builtin_command(const char *cmd)
{
	if (!ft_strcmp(cmd, ECHO_CMD))
		return (ECH);
	if (!ft_strcmp(cmd, CD_CMD))
		return (CD);
	if (!ft_strcmp(cmd, PWD_CMD))
		return (PWD);
	if (!ft_strcmp(cmd, ENV_CMD))
		return (ENV);
	if (!ft_strcmp(cmd, EXPORT_CMD))
		return (EXPORT);
	if (!ft_strcmp(cmd, UNSET_CMD))
		return (UNSET);
	if (!ft_strcmp(cmd, EXIT_CMD))
		return (EXIT);
	return (UNKNOWN);
}

int	execute_builtin(t_hell *hell, t_env **head, t_builtin cmd)
{
	if (cmd == ECH)
		return (my_echo(hell));
	if (cmd == CD)
		return (ft_cd(hell, head));
	if (cmd == PWD)
		return (ft_pwd(head, hell));
	if (cmd == ENV)
		return (ft_env(hell));
	if (cmd == EXPORT)
		return (ft_export(hell));
	if (cmd == UNSET)
		return (ft_unset(hell, hell->arguments));
	if (cmd == EXIT)
		return (my_exit(hell));
	return (ft_check_path(hell, head));
}

// executing builtin commands or usual (by path)
//If the command is valid (i.e., `cmd` is not equal to `7`),
// resulting error code from the command execution ->a string 
// update the env var `?` with this value using `ft_add_or_replace`
int	ft_is_builtins(t_hell *hell, t_env **head)
{
	t_builtin	cmd;
	int			errorcheck;
	char		*value;

	cmd = get_builtin_command(hell->arguments[0]);
	errorcheck = execute_builtin(hell, head, cmd);
	if (cmd != 7)
	{
		value = ft_itoa(errorcheck);
		ft_add_or_replace(head, "?", value);
		free(value);
	}
	return (errorcheck);
}

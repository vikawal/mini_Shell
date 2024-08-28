/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:16:17 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/08/23 01:53:59 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hell.h"

void	nrerror(int code, char *type, t_env **env)
{
	if (type && *type == -1)
	{
		(write (2, "hell: ambiguous redirect\n", 26), \
		ft_add_or_replace(env, "?", "1"));
		return ;
	}
	if (code == 1)
		(write (2, "hell: permission denied: ", 26), \
		ft_add_or_replace(env, "?", "1"));
	if (code == 2)
		(write (2, "hell: no such file or directory: ", 34), \
		ft_add_or_replace(env, "?", "1"));
	if (code == 3)
		(write (2, "hell: command not found: ", 26), \
		ft_add_or_replace(env, "?", "127"));
	if (code == 4)
		(write(2, "hell: played with redirections and lost", 40), \
		ft_add_or_replace(env, "?", "2"));
	if (code == 5)
		(write(2, "hell: WHY DO YOU PLAY WITH MALLOCS???", 38), \
		ft_add_or_replace(env, "?", "2"));
	if (type && *type != -1)
		write (2, type, ft_strlen(type));
	write(2, "\n", 1);
}

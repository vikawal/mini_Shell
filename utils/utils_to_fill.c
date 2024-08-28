/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 05:39:33 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/08/23 05:40:50 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hell.h"

int	count(t_hell *hell, char **args, int i)
{
	int	ret;

	ret = 0;
	while (args && args[i] && args[i][0] != '|')
	{
		if (args[i][0] && (args[i][0] == '<' || args[i][0] == '>') \
			&& args[i + 1] && args[i + 1][0] != '<' && args[i + 1][0] != '>' \
			&& args[i + 1][0] != '|')
			i = i + 2;
		else if ((args[i][0] && (args[i][0] == '<' || args[i][0] == '>')))
			return (hell->run = -1, nrerror(4, NULL, &(hell->env)), 0);
		else
		{
			ret++;
			i++;
		}
	}
	while (args && args[i] && args[i][0])
	{
		if (args[i][0] == '|' && (!args[i + 1] || i == 0))
			return (hell->run = -1, nrerror(4, NULL, &(hell->env)), 0);
		else
			i++;
	}
	return (ret);
}

void	redo_args(t_hell *hell)
{
	char	**replace;
	int		loc_count;
	int		i;

	i = 0;
	loc_count = 0;
	while (hell->arguments[i])
		if (hell->arguments[i++][0] != -1)
			loc_count++;
	if (i == loc_count)
		return ;
	replace = ft_calloc((loc_count + 1), sizeof(char *));
	i = 0;
	loc_count = 0;
	while (hell->arguments[i])
	{
		if (hell->arguments[i][0] != -1)
			replace[loc_count++] = hell->arguments[i++];
		else
			free(hell->arguments[i++]);
	}
	i = 0;
	replace[loc_count] = NULL;
	free(hell->arguments);
	hell->arguments = replace;
}

void	get_heredocs(t_hell *hell, int i, char **args)
{
	if (i == 0)
	{
		while (hell->arguments[i] && hell->run >= 0)
		{
			if (args[i] && args[i][0] == '<' && args[i][1] == '<')
			{
				args[i + 1] = ft_kill_quo(args[i + 1], 0, 0, -1);
				if (!args[i + 1])
					hell->run = -2;
				if (hell->run == -1)
					return ;
				heredoc(hell, &i, args[1 + i]);
				if (hell->run == -1)
					return ;
			}
			else
				i++;
		}
	}
}

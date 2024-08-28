/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makefds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:41:47 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/08/28 12:04:56 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hell.h"

void	makeout(t_hell *hell, int *i, char **args)
{
	(*i)++;
	place_dollar(&(args[*i]), hell->env, 0, hell);
	args[*i] = ft_kill_quo(args[*i], 0, 0, -1);
	if (!args[*i])
		hell->run = -2;
	if (hell->outfile > 0 && hell->run > 0)
		close(hell->outfile);
	if (args[*i - 1][1] != '>' && hell->run > 0 && args[*i][0] != -1)
		hell->outfile = open(args[*i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (args[*i - 1][1] == '>' && hell->run > 0 && args[*i][0] != -1)
		hell->outfile = open(args[*i], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if ((access(args[*i], F_OK) != -1 && access(args[*i], R_OK) == -1 && \
		hell->run > 0) || args[*i][0] == -1)
	{
		hell->run = 0;
		hell->outfile = -1;
		nrerror(1, args[*i], &(hell->env));
		while (args[*i] && args[*i][0] != '|')
			(*i)++;
	}
	else
		(*i)++;
}

void	makein(t_hell *hell, int *i, char **args)
{
	place_dollar(&(args[(*i) + 1]), hell->env, 0, hell);
	args[(*i) + 1] = ft_kill_quo(args[(*i) + 1], 0, 0, -1);
	if (!args[(*i) + 1])
		hell->run = -2;
	if (hell->infile > 0 && hell->run > 0)
		close(hell->infile);
	if (hell->run > 0)
		hell->infile = open(args[(*i) + 1], O_RDONLY);
	if (access(args[(*i) + 1], F_OK) == -1 && hell->run > 0)
	{
		hell->run = 0;
		nrerror(2, args[(*i) + 1], &(hell->env));
	}
	else if (access(args[(*i) + 1], R_OK) == -1 && hell->run > 0)
		hell->run = 0;
	if (hell->run == 0)
	{
		if (ft_strcmp(ft_search_in_list(&(hell->env), "?")->value, "1"))
			nrerror(1, args[(*i) + 1], &(hell->env));
		hell->infile = -1;
		while (args[*i] && args[*i][0] != '|')
			(*i)++;
	}
	else
		(*i) += 2;
}

void	get_in_here(t_hell *hell, int *i, int *hc)
{
	char	*for_here;

	(*i) += 2;
	for_here = local_join("/tmp/heredoc", ft_itoa((*hc)++));
	if (!for_here)
	{
		hell->run = -2;
		return ;
	}
	if (hell->infile)
		close(hell->infile);
	if (access(for_here, R_OK) == -1 || access(for_here, F_OK) == -1)
	{
		hell->run = 0;
		hell->infile = -1;
		nrerror(5, NULL, &(hell->env));
		while (hell->arguments[*i] && hell->arguments[*i][0] != '|')
			(*i)++;
	}
	hell->infile = open(for_here, O_RDONLY);
	free(for_here);
}

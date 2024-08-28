/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_hell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 09:13:49 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/08/24 15:47:39 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hell.h"

int		count(t_hell *hell, char **args, int i);
void	redo_args(t_hell *hell);
void	get_heredocs(t_hell *hell, int i, char **args);

char	*fill_this(t_hell *hell, char **arguments, int *i, int *hc)
{
	char	*ret;

	ret = NULL;
	if (arguments[*i] && arguments[*i][0] == '<' && arguments[*i][1] == 0)
		makein(hell, i, arguments);
	if (arguments[*i] && arguments[*i][0] == '>' && hell->run > 0)
		makeout(hell, i, arguments);
	if (arguments[*i] && arguments[*i][0] == '<' && arguments[*i][1] == '<' && \
		hell->run > 0)
		get_in_here(hell, i, hc);
	if (arguments[*i] && arguments[*i][0] != '<' && arguments[*i][0] != '>' && \
		arguments[*i][0] != '|' && hell->run > 0)
	{
		if (place_dollar(&(arguments[*i]), hell->env, 0, hell))
			return (hell->run = -2, NULL);
		arguments[*i] = ft_kill_quo(arguments[*i], 0, 0, -1);
		if (!arguments[*i])
			return (hell->run = -2, NULL);
		ret = malloc(ft_strlen(arguments[*i]) + 1);
		if (!ret)
			return (hell->run = -2, NULL);
		ft_strlcpy(ret, arguments[*i], ft_strlen(arguments[*i]) + 1);
		(*i)++;
	}
	return (ret);
}

t_hell	*finishup(t_hell *hell, int j, char **rpl)
{
	int	i;

	i = 0;
	rpl[j] = NULL;
	if (hell->run < 0)
		return (freeargs(&rpl), hell);
	if (hell->next && hell->next->run < 0)
		return (hell->run = hell->next->run, freeargs(&rpl), hell);
	while (hell->arguments && hell->arguments[i])
		free(hell->arguments[i++]);
	free(hell->arguments);
	hell->arguments = rpl;
	redo_args(hell);
	return (hell);
}

void	do_pipes(t_hell *hell, int i, int hc, char **arguments)
{
	int	pipefd[2];

	hell->next = fill_the_hell(init_hell(hell->env),
			i + 1, hc, arguments);
	if (pipe(pipefd) != -1)
	{
		hell->pipe = 1;
		hell->next->pipe = 1;
		if (!hell->next->infile)
			hell->next->infile = pipefd[0];
		else
			close(pipefd[0]);
		if (!hell->outfile)
			hell->outfile = pipefd[1];
		else
			close(pipefd[1]);
	}
	else
		hell->run = -2;
}

t_hell	*fill_the_hell(t_hell *hell, int i, int hc, char **arguments)
{
	char	**rpl;
	int		args;
	char	*temp;
	int		j;

	j = 0;
	args = count(hell, arguments + i, 0);
	rpl = malloc((args + 1) * sizeof(char *));
	get_heredocs(hell, i, arguments);
	if (!rpl)
		return (hell->run = -2, freeargs(&rpl), hell);
	while (arguments[i] && hell->run > -1 && !hell->next)
	{
		if (arguments[i] && arguments[i][0] != '|' && hell->run > 0)
		{
			temp = fill_this(hell, arguments, &i, &hc);
			if (temp)
				rpl[j++] = temp;
		}
		else if (arguments[i] && arguments[i][0] == '|' && hell->run >= 0)
			do_pipes(hell, i, hc, arguments);
		else
			i++;
	}
	return (finishup(hell, j, rpl));
}

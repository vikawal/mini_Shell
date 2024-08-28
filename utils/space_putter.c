/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_putter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:05:46 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/08/10 04:00:55 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hell.h"

int	quotes(char *input, int pos)
{
	int	i;
	int	base;
	int	count;

	count = 0;
	i = 0;
	base = 0;
	while (input[i] && i <= pos)
	{
		if (input[i] == '\'' && (base == 0 || base == 1))
		{
			count++;
			base = 1;
		}
		if (input[i] == '"' && (base == 0 || base == 2))
		{
			count++;
			base = 2;
		}
		i++;
		if (count % 2 == 0)
			base = 0;
	}
	return (base);
}

void	the_inserter(char *input, char *new_input, int *i, int *j)
{
	if ((input[*i] == '<' || input[*i] == '>') && !quotes(input, *i) && \
		(*i == 0 || new_input[*j - 1] != input[*i]))
	{
		if (*i == 0 || input[*i - 1] != ' ')
			new_input[(*j)++] = ' ';
		new_input[(*j)++] = input[(*i)++];
		if (input[*i] && input[*i] == input[*i - 1])
			new_input[(*j)++] = input[(*i)++];
		if (input[*i] && input[*i] != ' ' && !quotes(input, (*i) - 1))
			new_input[(*j)++] = ' ';
	}
	else if (input[*i] == '|' && !quotes(input, *i))
	{
		if (*i == 0 || input[*i - 1] != ' ')
			new_input[(*j)++] = ' ';
		new_input[(*j)++] = input[(*i)++];
		if (input[*i] && input[*i] != ' ' && !quotes(input, *i))
			new_input[(*j)++] = ' ';
	}
	else
		new_input[(*j)++] = input[(*i)++];
	return ;
}

char	*space_putter(t_hell *hell, char *input, int i, int j)
{
	char	*new_input;

	if (input && hell)
	{
		new_input = (char *)malloc((3 * strlen(input) + 1) * sizeof(char));
		if (!new_input)
			return (hell->run = -2, NULL);
		while (input[i])
			the_inserter(input, new_input, &i, &j);
		new_input[j] = 0;
		if (*input)
			add_history(input);
		free(input);
		hell->arguments = ft_split(new_input, ' ');
		free(new_input);
		if (!hell->arguments)
			return (hell->run = -2, NULL);
		return (NULL);
	}
	return (free(input), NULL);
}

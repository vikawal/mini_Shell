/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_the_hell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:14:50 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/08/17 20:17:30 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hell.h"

void	freeargs(char ***res)
{
	int	j;

	j = 0;
	if (*res)
	{
		while ((*res)[j])
		{
			free ((*res)[j]);
			(*res)[j] = NULL;
			j++;
		}
	}
	free (*res);
	*res = NULL;
}

void	fth(t_hell *hell, t_env **envire)
{
	if (!hell)
		return ;
	if (hell->env != *envire)
		*envire = hell->env;
	if (hell->path)
		free(hell->path);
	if (hell->arguments)
		freeargs(&hell->arguments);
	if (hell->next)
		fth(hell->next, envire);
	free(hell);
}

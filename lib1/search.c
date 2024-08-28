/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:19:07 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/06/07 16:54:51 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*search(char *s, char c)
{
	int		check;
	int		base;

	base = 0;
	check = -1;
	while (*s != 0)
	{
		if (*s == '\"' && (base == 0 || base == 2))
		{
			check *= -1;
			base = 2;
		}
		if (*s == '\'' && (base == 0 || base == 1))
		{
			check *= -1;
			base = 1;
		}
		if (*s == c && check == -1)
			return (s);
		s++;
		if (check == -1)
			base = 0;
	}
	return (NULL);
}

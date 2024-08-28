/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:39:47 by ovolzhev          #+#    #+#             */
/*   Updated: 2023/12/12 19:52:08 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!s2)
		return (free(s1), NULL);
	if (!s1)
		j = 0;
	else
		j = ft_strlen(s1);
	i = 0;
	res = (char *)ft_calloc(j + ft_strlen(s2) + 1, 1);
	if (!res)
		return (free(s1), NULL);
	while (i < j + ft_strlen(s2))
	{
		if (i < j)
			res[i] = s1[i];
		else
			res[i] = s2[i - j];
		i++;
	}
	res[i] = 0;
	free (s1);
	return (res);
}

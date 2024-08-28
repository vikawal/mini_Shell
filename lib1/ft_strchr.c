/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:41:32 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/06/05 21:58:22 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*res;

	if (!str)
		return (NULL);
	c = c % 256;
	res = (char *)str;
	while (*res != 0)
	{
		if (*res == c)
			return (res);
		res++;
	}
	if (c == 0)
		return (res);
	return (NULL);
}

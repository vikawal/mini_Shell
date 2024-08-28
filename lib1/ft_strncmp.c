/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:37:00 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/06/10 10:43:39 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	b;

	i = 0;
	if (n == 0)
		return (0);
	if (!str1)
		return (1);
	while (i < n && (str1[i] || str2[i]))
	{
		a = str1[i];
		b = str2[i];
		if (a != b)
			return (a - b);
		i++;
	}
	return (str1[i - 1] - str2[i - 1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:09:18 by ovolzhev          #+#    #+#             */
/*   Updated: 2023/12/11 18:14:38 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	symbcount(int n)
{
	int	res;

	res = 0;
	while (n != 0)
	{
		n /= 10;
		res++;
	}
	return (res);
}

static char	*filling(int n, char *res, int symbols)
{
	int	bruh;

	res[symbols] = 0;
	while ((symbols - 1) >= 0 && n != 0)
	{
		if (n < 0)
			bruh = -(n % 10) + 48;
		else
			bruh = (n % 10) + 48;
		res[symbols - 1] = bruh;
		n /= 10;
		symbols--;
	}
	if (symbols == 1)
		res[0] = '-';
	return (res);
}

char	*ft_itoa(int n)
{
	int		symbols;
	char	*res;

	if (n == 0)
	{
		res = ft_calloc(2, sizeof(char));
		if (!res)
			return (NULL);
		res[0] = '0';
		return (res);
	}
	symbols = symbcount(n);
	if (n < 0)
		symbols++;
	res = ft_calloc((symbols + 1), sizeof(char));
	if (!res)
		return (NULL);
	res = filling(n, res, symbols);
	return (res);
}

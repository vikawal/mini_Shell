/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:37:00 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/08/12 02:37:50 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*helper(char *big, char *little, size_t len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (len > 0)
	{
		if (big[i] == little[j])
		{
			while (big[i + j] == little[j] && len > 0)
			{
				j++;
				len--;
				if (little[j] == 0)
					return ((char *)& big[i]);
			}
			len = len + j;
			j = 0;
		}
		i ++;
		len--;
	}
	return (NULL);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	if (*big == 0 && *little)
		return (NULL);
	if (*big == 0 || *little == 0)
		return ((char *)big);
	return (helper((char *)big, (char *)little, len));
}

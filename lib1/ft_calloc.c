/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:54:19 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/08/23 04:35:56 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*res;

	if ((nitems > LONG_MAX && size > 0) || (size > LONG_MAX && nitems > 0))
		return (NULL);
	res = malloc(nitems * size);
	if (!res)
		return (NULL);
	ft_bzero(res, nitems * size);
	return (res);
}

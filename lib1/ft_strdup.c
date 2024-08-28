/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:31:39 by vmyshko           #+#    #+#             */
/*   Updated: 2024/08/22 22:20:32 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <string.h>
// #include <stdlib.h>
// #include <stdio.h>
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == 0 && src == 0)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	length;

	if (!s)
		return (NULL);
	length = ft_strlen(s) + 1;
	dest = malloc(length);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s, length);
	return (dest);
}

// int main ()
// {
// 	char src[] = "Hello, strdup!";
// 	char *result_1 = ft_strdup(src);
// 	char *result_2 = strdup(src);
// 	printf("Start string: %s\n", src);
// 	printf("My strdup: %s\n", result_1);
// 	printf("Original strdup: %s\n", result_2);
// 	free(result_1);
// 	free(result_2);
// 	return (0);
// }
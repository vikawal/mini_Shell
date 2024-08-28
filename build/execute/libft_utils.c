/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:30:52 by vmyshko           #+#    #+#             */
/*   Updated: 2024/08/23 17:48:05 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hell.h"
//USED
int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	end;

	i = 0;
	while (dst[i] && i < size)
	{
		i++;
	}
	end = ft_strlcpy(dst + i, src, size - i);
	return (end + i);
}

char	*my_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	if (!s1)
		return (NULL);
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = len1 + len2;
	s3 = malloc(sizeof(char) * (len3 + 1));
	if (!s3)
		return (NULL);
	ft_strlcpy(s3, s1, len1 + 1);
	ft_strlcat(s3, s2, len3 + 1);
	return (s3);
}

void	delhere(void)
{
	char	*filename;
	int		i;

	i = 0;
	filename = local_join("/tmp/heredoc", ft_itoa(i++));
	while (filename && access(filename, F_OK) == 0)
	{
		unlink(filename);
		free(filename);
		filename = local_join("/tmp/heredoc", ft_itoa(i++));
	}
	free(filename);
}

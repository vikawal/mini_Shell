/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:39:47 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/07/03 21:35:29 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char const *set)
{
	size_t	i;
	int		start_rem;
	int		end_rem;
	char	*res;
	char	*temp;

	if (s1 == NULL)
		return (NULL);
	res = 0;
	start_rem = 0;
	end_rem = 0;
	i = ft_strlen(s1);
	while (ft_strchr(set, s1[start_rem]))
		start_rem++;
	while (start_rem + end_rem < (int)i && ft_strchr(set, s1[i - end_rem - 1]))
		end_rem++;
	if (start_rem + end_rem == (int)i)
		return (malloc (0));
	temp = malloc(ft_strlen(s1));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, s1, ft_strlen(s1));
	res = ft_substr(temp, start_rem, i - start_rem - end_rem);
	return (res);
}

char	*ft_frstrtrim(char *s1, char const *set)
{
	size_t	i;
	int		start_rem;
	int		end_rem;
	char	*res;

	if (s1 == NULL)
		return (NULL);
	res = 0;
	start_rem = 0;
	end_rem = 0;
	i = ft_strlen(s1);
	while (ft_strchr(set, s1[start_rem]))
		start_rem++;
	while (start_rem + end_rem < (int)i && ft_strchr(set, s1[i - end_rem - 1]))
		end_rem++;
	if (start_rem + end_rem == (int)i)
		return (free (s1), malloc (0));
	res = ft_substr(s1, start_rem, i - start_rem - end_rem);
	return (res);
}

char	*ft_kill_quo(char *s, int i, int base, int check)
{
	char	*ret;
	char	*f;

	f = s;
	ret = malloc(ft_strlen(s) + 1);
	if (!ret)
		return (free(f), NULL);
	while (s && *s)
	{
		if (*s == '\"' && (base == 0 || base == 2 || check == -1))
		{
			check *= -1;
			base = 2;
			s++;
		}
		else if (*s == '\'' && (base == 0 || base == 1 || check == -1))
		{
			check *= -1;
			base = 1;
			s++;
		}
		else if (*s)
			ret[i++] = *s++;
	}
	return (ret[i] = 0, free(f), ft_substr(ret, 0, i + 1));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:29:58 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/06/27 17:14:02 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	helper(char *s, char c, int words, char **res);
static char	**ifspace(void);
static void	freer(char **res, int j);
static int	wordcount(char *s, int i, char c, int words);

char	**ft_split(char *s, char c)
{
	int		checker;
	int		words;
	char	**res;

	if (s == NULL)
		return (NULL);
	if (*s == 0 || !ft_strncmp(s, "", 1))
		return (ifspace());
	while (*s == c)
		s++;
	if (*s != 0)
	{
		words = wordcount(s, 0, c, 0);
		res = (char **)malloc((words + 1) * sizeof(char *));
		if (res == NULL)
			return (NULL);
		checker = helper (s, c, words, res);
		if (checker == -1)
			return (NULL);
		res [checker] = NULL;
	}
	else
		res = ifspace();
	return (res);
}

static int	helper(char *s, char c, int words, char **res)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < (size_t)words)
	{
		if (*s == c)
			s++;
		else
		{
			i = (ft_strlen(s) + 1);
			if (search(s, c))
				i = (search(s, c) - s + 1);
			res[j] = (char *)malloc((i) * sizeof(char));
			if (res[j] == NULL)
				return (freer(res, j), -1);
			ft_strlcpy(res[j], s, i);
			j++;
			s += i;
		}
	}
	return ((int)j);
}

static char	**ifspace(void)
{
	char	**res;

	res = malloc(sizeof(char *));
	if (!res)
		return (NULL);
	res[0] = NULL;
	return (res);
}

static void	freer(char **res, int j)
{
	while (j >= 0)
	{
		free (res[j]);
		j--;
	}
	free (res);
}

static int	wordcount(char *s, int i, char c, int words)
{
	int	check;
	int	base;

	base = 0;
	check = -1;
	while (s[i])
	{
		if (s[i] == '\"' && (base == 0 || base == 2))
		{
			check *= -1;
			base = 2;
		}
		if (s[i] == '\'' && (base == 0 || base == 1))
		{
			check *= -1;
			base = 1;
		}
		if (s[i] != c && s[i] != 0 && (s[i + 1] == 0 || s[i + 1] == c) \
			&& check == -1)
			words++;
		i++;
		if (check == -1)
			base = 0;
	}
	return (words);
}

//	char **res;
// 	int i = 0;
// 	char str[30] = "grekknbfsjese";
// 	res = ft_split(str, 'e');
// 	while (res[i])
// 	{
// 		printf("%s,", res[i]);
// 		free(res[i]);
// 		i++;
// 	}
// 	printf("%s.", res[i]);
// 	free (res[i]);
// 	free (res);

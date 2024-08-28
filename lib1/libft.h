/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:06:20 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/08/21 13:37:43 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <bsd/string.h>
# include <fcntl.h>
//isfuncs
int		ft_isdigit(int x);

// //strfuncs0
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *str, int c);
char	*search(char *s, char c);

// //strfuncs1
void	ft_bzero(void *s, size_t n);

// //leftovers
void	*ft_calloc(size_t nitems, size_t size);

// //additionals
char	*ft_strjoin(char *s1, char const *s2);

char	*ft_itoa(int n);

// //files
char	**ft_split(char *s, char c);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strtrim(char *s1, char const *set);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_frstrtrim(char *s1, char const *set);
char	*ft_kill_quo(char *s, int i, int base, int check);

//added by Vika
char	*ft_strdup(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strnstr(const char *big, const char *little, size_t len);

#endif

//kind of fun, kind of cool, kind of awesome
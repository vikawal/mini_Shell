/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 05:32:32 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/08/28 12:17:02 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hell.h"

char	*get_value(char *key, t_env *env)
{
	char	*ret;

	ret = NULL;
	if (!key || !env)
		return (NULL);
	while (env && ft_strncmp(env->key, key, ft_strlen(env->key) + 1))
		env = env->next;
	if (env)
		ret = env->value;
	return (ret);
}

int	get_key_len(char **arg, int start, int i, char *key)
{
	key = ft_strchr(*arg + start, '$') + 1;
	while ((key[i] >= 65 && key[i] <= 90) || (key[i] >= 48 && \
		key[i] <= 57 && i != 0) || key[i] == '_' || \
		(key[i] >= 'a' && key[i] <= 'z'))
		i++;
	if (i == 0 && ((key[i] >= 48 && key[i] <= 57) || key[i] == '?'))
		i = 1;
	return (i);
}

char	*place_the_thing(char **arg, int start, char *key, t_env *env)
{
	char	*value;
	char	*ret;

	value = get_value(key, env);
	ret = ft_calloc(ft_strlen(value) + ft_strlen(*arg) - ft_strlen(key) + 2, 1);
	if (!ret)
		return (free(key), NULL);
	ft_strlcpy(ret, *arg, ft_strchr(*arg + start, '$') - *arg + 1);
	ft_strlcpy(ret + (ft_strchr(*arg + start, '$') - *arg), value,
		ft_strlen(value) + 1);
	ft_strlcpy(ret + (ft_strchr(*arg + start, '$') - *arg) + ft_strlen(value),
		(ft_strchr(*arg + start, '$') + ft_strlen(key) + 1),
		ft_strlen(ft_strchr(*arg, '$') + ft_strlen(key)) + 1);
	free(*arg);
	if (ret[0] == 0)
		ret[0] = -1;
	return (ret);
}

int	place_dollar(char **arg, t_env *env, int start, t_hell *hell)
{
	char	*value;
	char	*key;
	char	*ret;
	int		i;

	if (!ft_strchr(*arg + start, '$'))
		return (0);
	if (quotes(*arg, ft_strchr(*arg + start, '$') - *arg) == 1)
		return (place_dollar(arg, env, start + 1, hell));
	i = get_key_len(arg, start, 0, NULL);
	if (i == 0)
		return (place_dollar(arg, env, start + 1, hell));
	key = ft_calloc(i + 1, 1);
	if (!key)
		return (-1);
	ft_strlcpy(key, ft_strchr(*arg + start, '$') + 1, i + 1);
	value = get_value(key, env);
	ret = place_the_thing(arg, start, key, env);
	if (!ret)
		return (-1);
	if (ft_strchr(ret + ft_strlen(value), '$'))
		place_dollar(&ret, env, start + ft_strlen(value), hell);
	*arg = ret;
	return (free(key), 0);
}

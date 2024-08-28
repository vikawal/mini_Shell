/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 01:31:48 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/08/26 12:30:55 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hell.h"

void	free_env(t_env *ret)
{
	if (ret->key)
		free(ret->key);
	ret->key = NULL;
	if (ret->value)
		free(ret->value);
	ret->value = NULL;
	if (ret->next)
		free_env(ret->next);
	ret->next = NULL;
	free (ret);
}

t_env	*init_env(t_env	*ret, char *key, char *value)
{
	ret = malloc(sizeof(t_env));
	if (!ret)
		return (NULL);
	if (value && *value == '=')
	{
		*value = 0;
		value++;
	}
	ret->key = malloc(ft_strlen(key) + 1);
	if (!ret->key)
		return (free(ret), NULL);
	ft_strlcpy(ret->key, key, ft_strlen(key) + 1);
	ret->env = 1;
	ret->next = NULL;
	ret->value = NULL;
	if (!ft_strcmp(key, "?"))
		ret->env = 0;
	if (!value)
		return (ret->env = 0, ret);
	ret->value = malloc(ft_strlen(value) + 1);
	if (!ret->value)
		return (free(ret), free(ret->key), NULL);
	ft_strlcpy(ret->value, value, ft_strlen(value) + 1);
	return (ret);
}

void	get_shell(t_env *ret, char **argv)
{
	char	*pwd;
	char	*argument;
	int		i;

	i = 0;
	while (argv[i] && !ft_strnstr(argv[i], "minishell", ft_strlen(argv[i])))
		i++;
	argument = ft_strdup(argv[i]);
	if (argument[0] == '/')
		;
	else
	{
		if (argument[0] == '.' && argument[1] != '.')
			argument = ft_frstrtrim(argument, ".");
		if (argument[0] == '.')
			argument = local_join("/", argument);
		pwd = getcwd(NULL, 0);
		argument = local_join(pwd, argument);
		free(pwd);
	}
	ft_add_or_replace(&ret, "SHELL", argument);
	ft_add_or_replace(&ret, "_", argument);
	free(argument);
}

t_env	*env_exists(t_env *ret, char **envp, t_env *temp, int i)
{
	ret = init_env(NULL, envp[0], ft_strchr(envp[0], '='));
	if (!ret)
		return (NULL);
	i = 1;
	temp = ret;
	while (envp[i])
	{
		temp->next = init_env(temp, envp[i], ft_strchr(envp[i], '='));
		if (!temp->next)
			return (free_env(ret), NULL);
		temp = temp->next;
		i++;
	}
	temp->next = init_env(temp, "?", "0");
	return (ret);
}

t_env	*setup_env(char **envp, char **argv)
{
	t_env	*ret;
	char	*lvl;

	if (envp[0])
		ret = env_exists(NULL, envp, NULL, 0);
	else
	{
		lvl = getcwd(NULL, 0);
		ret = init_env(NULL, "PWD", lvl);
		free(lvl);
	}
	if (!ft_search_in_list(&ret, "SHLVL"))
		lvl = ft_calloc(2, 1);
	else
		lvl = ft_strdup(ft_search_in_list(&ret, "SHLVL")->value);
	if (!lvl)
		return (free_env(ret), NULL);
	if (!lvl[0])
		lvl[0] = '0';
	ft_add_or_replace(&ret, "SHLVL", ft_itoa(1 + ft_atoi_long(lvl)));
	(get_shell(ret, argv), free(lvl));
	return (ret);
}

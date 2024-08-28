/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:37:31 by vmyshko           #+#    #+#             */
/*   Updated: 2024/08/26 12:23:21 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hell.h"

int	ft_print_export(t_hell *hell)
{
	t_env	*sort_list;
	t_env	*newnode;
	int		out;

	sort_list = ft_sort_list(hell->env);
	newnode = sort_list;
	out = hell->outfile;
	if (!out)
		out = 1;
	while (newnode != NULL)
	{
		if (newnode->key[0] != '?' && ft_strcmp("_", newnode->key))
		{
			(ft_putstr_fd("declare -x ", out), ft_putstr_fd(newnode->key, out));
			if (newnode->value != NULL)
			{
				(ft_putstr_fd("=\"", out), ft_putstr_fd(newnode->value, out));
				ft_putchar_fd('"', out);
			}
			ft_putchar_fd('\n', out);
		}
		newnode = newnode->next;
	}
	ft_destroy_env_list(sort_list);
	return (0);
}

/**
 * Special handling is included for the environment variable `SHLVL`, 
 * where the dynamically allocated `value` is freed
 * after use. This prevents memory leaks from temporary allocations.
 */
void	ft_add_or_replace(t_env **head, char *key, char *value)
{
	t_env	*node;
	t_env	*newnode;

	node = ft_search_in_list(head, key);
	if (node != NULL)
	{
		if (node->value)
			free(node->value);
		if (value && value[0] == '=')
			value++;
		node->value = ft_strdup(value);
		if (node->value && node->key[0] != '?')
			node->env = 1;
	}
	else
	{
		node = *head;
		newnode = init_env(NULL, key, value);
		while (node->next)
			node = node->next;
		node->next = newnode;
	}
	if (!ft_strcmp("SHLVL", key))
		free(value);
}

/**
 * ft_add_or_append_var - Adds or appends to an env var in the shell.
 * if the provided `key` ends with a `+` to determine if it should
 * append to the existing env var's value. If the `+` is -> it is
 * removed, and the function appends `value` to the existing var's value.
 * If the var does not exist, or if no `+`, it adds or replaces the var
 * with the new `key` and `value`.
 */
void	ft_add_or_append_var(t_hell *hell, char *key, char *value,
		size_t key_len)
{
	t_env	*node;
	char	*new_value;

	if (key[key_len - 1] == '+')
	{
		key[key_len - 1] = '\0';
		node = ft_search_in_list(&hell->env, key);
		if (node)
		{
			new_value = my_strjoin(node->value, value);
			free(node->value);
			node->value = new_value;
		}
		else
			ft_add_or_replace(&hell->env, key, value);
	}
	else
		ft_add_or_replace(&hell->env, key, value);
}

/**
 * handles parsing a string that represents an env var assignment.
 * It detects if the shell is in a pipeline and skips variable modification.
 * If the argument contains an `=` sign, it is split into a `key` and `value`, 
 * which are then processed to add or update the environment variable. 
 * If the key ends with a `+`, the value is appended to the existing variable. 
 * If no `=` is found, the argument is added as a variable
 * with no associated value.
 */
void	ft_parse_and_add_var(t_hell *hell, char *arg)
{
	char	*eq_pos;
	size_t	key_len;
	char	*key;
	char	*value;

	if (hell->pipe)
		return ;
	eq_pos = ft_strchr(arg, '=');
	if (eq_pos)
	{
		key_len = eq_pos - arg;
		key = ft_strndup(arg, key_len);
		if (*(eq_pos + 1) != '=')
			value = ft_strdup(eq_pos + 1);
		else
			value = ft_strdup(eq_pos);
		ft_add_or_append_var(hell, key, value, key_len);
		free(key);
		free(value);
	}
	else
		ft_add_or_replace(&hell->env, arg, NULL);
}

/**
 * ft_export - Handles the export of environment variables in the shell.
 * 1) either display all environment variables in the current shell (!=args)
 *  or to add/update environment variables based on the provided
 * arguments. If arguments are provided, it validates each argument to ensure
 * it follows the correct format for environment variable assignments, 
 * and then adds or updates the variables accordingly.
 *
 * If output redirection is detected (outfile > 2), the function closes 
 * the output file descriptor after printing. It returns `0` on success 
 * or the error code of the last invalid argument processed.
 *
 * Return: 0 on success, or error code of the last invalid argument processed.
 */

int	ft_export(t_hell *hell)
{
	int	ret;
	int	i;

	i = 1;
	ret = 0;
	if (hell->arguments[1] == NULL)
	{
		ft_print_export(hell);
		if (hell->outfile > 2)
			close(hell->outfile);
		return (0);
	}
	while (hell->arguments[i])
	{
		ret = ft_checkargs(hell->arguments[i]);
		if (!ret)
			ft_parse_and_add_var(hell, hell->arguments[i]);
		i++;
	}
	return (ret);
}

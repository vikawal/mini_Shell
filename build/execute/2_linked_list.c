/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_linked_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:03:47 by vmyshko           #+#    #+#             */
/*   Updated: 2024/08/24 16:11:24 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hell.h"

//search for an env variable by its key in a linked list.
//If node is found -replace  current value with a new 
// If the key is not found in the list - do nothing.
void	ft_replaceit(t_env **head, char *key, char *value)
{
	t_env	*temp;

	temp = ft_search_in_list(head, key);
	if (temp != NULL)
	{
		free(temp->value);
		temp->value = ft_strdup(value);
	}
}

// void	*handle_malloc_failure(const char *msg)
// {
// 	perror(msg);
// 	return (NULL);
// }

// to use env in execve
// linked list of environment variables (each node  key/value)
//make it array of strings. Each string "KEY=VALUE".

char	**ft_list_to_arr(t_env **head)
{
	t_env	*temp;
	char	**env;
	int		i;
	char	*tmp_key;

	temp = *head;
	i = ft_count_list(head);
	env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (temp != NULL)
	{
		tmp_key = my_strjoin(temp->key, "=");
		if (!tmp_key)
			return (NULL);
		env[i] = my_strjoin(tmp_key, temp->value);
		i++;
		temp = temp->next;
	}
	env[i] = NULL;
	return (env);
}
//we create own copy own env to use, checking if 
//env var start with = or not

t_env	*ft_copy_list(t_env *head)
{
	t_env	*temp;
	t_env	*newnode;
	t_env	*copy;
	char	*eql;

	temp = head;
	copy = NULL;
	if (head == NULL)
		return (NULL);
	while (temp != NULL)
	{
		if (temp->value && temp->value[0] == '=')
			eql = my_strjoin("=", temp->value);
		else
			eql = ft_strdup(temp->value);
		newnode = init_env(NULL, temp->key, eql);
		free(eql);
		if (copy == NULL)
			copy = newnode;
		else
			ft_add_to_list(&copy, newnode);
		temp = temp->next;
	}
	return (copy);
}

// for buble sort in *ft_sort_list(t_env *head)
void	ft_swap_nodes(t_env	*temp)
{
	char	*tmp;

	if (ft_strcmp(temp->key, temp->next->key) > 0)
	{
		tmp = temp->next->key;
		temp->next->key = temp->key;
		temp->key = tmp;
		tmp = temp->next->value;
		temp->next->value = temp->value;
		temp->value = tmp;
	}
}
//bubble sort for printng export without arguments
//  based on  keys in lexicographical order.

t_env	*ft_sort_list(t_env *head)
{
	t_env	*temp;
	t_env	*sort_list;
	int		i;

	temp = head;
	sort_list = ft_copy_list(temp);
	i = ft_count_list(&sort_list);
	temp = sort_list;
	while (i > 0)
	{
		temp = sort_list;
		while (temp->next != NULL)
		{
			ft_swap_nodes(temp);
			temp = temp->next;
		}
		i--;
	}
	return (sort_list);
}

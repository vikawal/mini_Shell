/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:03:47 by vmyshko           #+#    #+#             */
/*   Updated: 2024/08/24 16:06:59 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hell.h"

t_env	*ft_create_node(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new)
	{
		new->key = ft_strdup(key);
		new->value = ft_strdup(value);
		new->next = NULL;
	}
	return (new);
}

void	ft_add_to_list(t_env **head, t_env *newnode)
{
	t_env	*list;

	if (!head || !newnode)
		return ;
	if (*head)
	{
		list = *head;
		while (list->next)
			list = list->next;
		list->next = newnode;
	}
	else
		*head = newnode;
}

int	ft_delete_first_node(t_env **head, t_env *temp, char *key)
{
	if (!(ft_strcmp(temp->key, key)))
	{
		*head = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
		return (1);
	}
	return (0);
}

void	ft_delete_from_list(t_env **head, char *key)
{
	t_env	*prev;
	t_env	*temp;

	temp = *head;
	if (*head == NULL)
		return ;
	if (ft_delete_first_node(head, temp, key))
		return ;
	while (temp != NULL && ft_strcmp(temp->key, key) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	else
	{
		prev->next = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

t_env	*ft_search_in_list(t_env **head, const char *key)
{
	t_env	*temp;

	temp = *head;
	if (temp == NULL)
		return (NULL);
	while (temp != NULL && ft_strcmp(temp->key, key) != 0)
		temp = temp->next;
	return (temp);
}

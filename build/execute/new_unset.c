/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:32:57 by vmyshko           #+#    #+#             */
/*   Updated: 2024/08/26 12:26:18 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hell.h"

int	ft_ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}

/**
 * Removes specified env variables from the shell environment.
 *  If a matching var is found, it is removed from the list, 
 * and its associated memory is freed. 
 * ensure that if there is a pipeline operation (`hell->pipe`), no
 * modifications are made to the environment.
 *
 * Return: Always returns 0 indicating successful execution.
 */
int	ft_unset(t_hell *hell, char **key)
{
	t_env	*current;
	t_env	*prev;
	int		i;

	i = 0;
	while (key[++i] && !hell->pipe)
	{
		current = hell->env;
		prev = NULL;
		while (current != NULL)
		{
			if (ft_ft_strcmp(current->key, key[i]) == 0)
			{
				if (prev == NULL)
					hell->env = current->next;
				else
					prev->next = current->next;
				(free(current->key), free(current->value), free(current));
				break ;
			}
			prev = current;
			current = current->next;
		}
	}
	return (0);
}

void	free_env_list(t_env *env_list)
{
	t_env	*temp;

	while (env_list != NULL)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

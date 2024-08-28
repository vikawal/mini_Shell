/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:19:05 by vmyshko           #+#    #+#             */
/*   Updated: 2024/08/24 15:48:09 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hell.h"

void	ft_destroy_env_list(t_env *head)
{
	t_env	*temp;
	t_env	*change;

	temp = head;
	if (head == NULL)
		return ;
	while (temp != NULL)
	{
		free(temp->key);
		free(temp->value);
		change = temp->next;
		free(temp);
		temp = change;
	}
}

int	ft_count_args(t_hell *hell)
{
	int		i;
	char	**args;

	i = 0;
	args = hell->arguments;
	if (args == NULL)
		return (0);
	while (args[i] != NULL)
		i++;
	return (i);
}

int	ft_put_err(char *input, char *message, int result)
{
	ft_putstr_fd("hell: ", 2);
	if (input != NULL)
		ft_putstr_fd(input, 2);
	ft_putendl_fd(message, 2);
	return (result);
}

int	is_num(char *str)
{
	errno = 0;
	if ((ft_atoi_long(str) == LLONG_MAX
			|| ft_atoi_long(str) == LLONG_MIN) && errno)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str == '\0')
		return (1);
	return (0);
}

long long	ft_atoi_long(const char *str)
{
	long long	result;
	int			sign;
	int			nb;
	int			i;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
	{
		nb = (str[i++] - 48);
		if (sign == 1 && (LLONG_MAX - result) / 10 < result)
			return (errno = ERANGE, LLONG_MAX);
		if (sign == -1 && (LLONG_MIN + result) / 10 > result)
			return (errno = ERANGE, LLONG_MIN);
		result = result * 10 + nb * sign;
	}
	return (result);
}

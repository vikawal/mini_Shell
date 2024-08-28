/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:13:02 by vmyshko           #+#    #+#             */
/*   Updated: 2024/08/26 12:19:40 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hell.h"

static int	check_new_line(t_hell *hell, int *i, int count)
{
	int		j;
	char	*str;
	int		ret;

	ret = 1;
	while (hell->arguments[count] && hell->arguments[count][0] == '-')
	{
		str = hell->arguments[count++];
		j = 1;
		if (!ft_strcmp(str, "-n"))
			ret = 0;
		if (!ft_strncmp(str, "-n", 2))
			while (str[j] && str[j++] == 'n')
				;
		if (j > 1 && str[j - 1] == 'n')
			ret = 0;
		else
		{
			count--;
			break ;
		}
	}
	(*i) = count;
	return (ret);
}

int	my_echo(t_hell *hell)
{
	int	i;
	int	newline;
	int	out;

	i = 1;
	out = hell->outfile;
	if (!out)
		out = STDOUT_FILENO;
	newline = check_new_line(hell, &i, 1);
	while (hell->arguments[i])
	{
		write(out, hell->arguments[i], ft_strlen(hell->arguments[i]));
		if (hell->arguments[++i])
			write(out, " ", 1);
	}
	if (newline)
		write(out, "\n", 1);
	if (!hell->next)
		ft_add_or_replace(&(hell->env), "?", "0");
	return (0);
}

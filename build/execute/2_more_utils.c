/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_more_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:19:05 by vmyshko           #+#    #+#             */
/*   Updated: 2024/08/28 12:16:44 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hell.h"

// FOR BUILT-IN new_export
// If the string contains an equal sign or any character other than alphanumeric
// or underscores, the function returns 1 to indicate invalidity.
int	checkstr(char *str)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_' \
		&& str[i] != '+' && str[i + 1] != '=')
			return (1);
		i++;
	}
	return (0);
}

// for new export validation of arguments
int	ft_checkargs(char *arg)
{
	char	*error;
	char	*join;
	int		ret;

	ret = 0;
	if (arg != NULL)
	{
		if (!ft_strcmp(arg, ""))
			ret = ft_put_err("export:", " `': not a valid identifier", 1);
		else if (!(ft_isalpha(arg[0]) || arg[0] == '_') || checkstr(arg))
		{
			join = my_strjoin(arg, "': not a valid identifier");
			error = my_strjoin(" `", join);
			free(join);
			ret = ft_put_err("export:", error, 1);
			free(error);
		}
	}
	return (ret);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	length;
	char	*dest;

	length = strnlen(s, n);
	dest = malloc(length + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s, length + 1);
	dest[length] = '\0';
	return (dest);
}
//NOT USED
// void	my_after_equal(char *str, char **s, int i)
// {
// 	int	j;

// 	j = 0;
// 	if (str[i] == '=' && str[i + 1] == '\0')
// 		s[1][0] = '\0';
// 	else if (str[i] == '\0')
// 	{
// 		free(s[1]);
// 		s[1] = NULL;
// 	}
// 	else
// 	{
// 		while (str[++i] != '\0')
// 			s[1][j++] = str[i];
// 		s[1][j] = '\0';
// 	}
// }
// FOR FT_EXECVE short
// env_arr = ft_list_to_arr(&env);
// 	if (!env_arr)
// 	{
// 		handle_error("ft_execve: ft_list_to_arr failed")
// 		perror("ft_execve: ft_list_to_arr failed");
// 		exit(EXIT_FAILURE);
// 	}

void	handle_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

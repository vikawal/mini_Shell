/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:09:10 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/08/23 01:01:54 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hell.h"

void	heredocsig(int sig)
{
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	close(STDIN_FILENO);
}

char	*local_join(const char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!s2)
		return (ft_strdup(s1));
	j = ft_strlen(s1);
	i = 0;
	res = (char *)ft_calloc(j + ft_strlen(s2) + 1, 1);
	if (!res)
		return (free(s2), NULL);
	while (i < j + ft_strlen(s2))
	{
		if (i < j)
			res[i] = s1[i];
		else
			res[i] = s2[i - j];
		i++;
	}
	res[i] = 0;
	free(s2);
	return (res);
}

int	make_doc(void)
{
	char	*filename;
	int		i;

	i = 0;
	filename = local_join("/tmp/heredoc", ft_itoa(i++));
	while (filename && access(filename, F_OK) == 0)
	{
		free (filename);
		filename = local_join("/tmp/heredoc", ft_itoa(i++));
	}
	if (!filename)
		return (-1);
	i = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(filename);
	return (i);
}

void	child(char *del)
{
	char	*buff;
	int		fd;	

	fd = make_doc();
	if (fd < 0)
		exit(2);
	signal(SIGINT, heredocsig);
	if (g_sig != 0)
		close(STDIN_FILENO);
	while (g_sig == 0)
	{
		buff = readline("> ");
		if (!buff || !ft_strncmp(del, buff, ft_strlen(del) + 1))
			break ;
		(write(fd, buff, ft_strlen(buff)), write(fd, "\n", 1));
		(free(buff), buff = NULL);
	}
	if (fd > 0)
		close(fd);
	free(buff);
	if (g_sig != 0)
		exit(1);
	exit(0);
}

void	heredoc(t_hell *hell, int *i, char *del)
{
	pid_t	pid;
	int		status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		hell->run = -3;
		return ;
	}
	if (!pid && !g_sig)
		child(del);
	wait(&status);
	if (status == 256)
	{
		hell->run = -1;
		g_sig = 1;
	}
	else if (status)
		hell->run = -2;
	(*i) += 2;
}

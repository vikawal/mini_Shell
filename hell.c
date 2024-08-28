/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ovolzhev <ovolzhev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:57:01 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/08/23 04:40:57 by ovolzhev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hell.h"

int		g_sig = 0;

int	count_b(char *s, int base, int glc)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == '\'' && (base == 0 || base == 1 || (count + glc) % 2 == 0))
		{
			count++;
			base = 1;
		}
		if (*s == '"' && (base == 0 || base == 2 || (count + glc) % 2 == 0))
		{
			count++;
			base = 2;
		}
		s++;
	}
	if ((count + glc) % 2 == 1)
		return (base);
	else
		return (0);
}

void	handle_sigint(int sig)
{
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
// ДОЛЖЕН ДЕЛАТЬ $? 130

char	*get_a_line(void)
{
	char	*input;
	int		quotes;

	input = readline("Enter a command: ");
	if (!input)
		return (NULL);
	quotes = count_b(input, 0, 0);
	if (quotes)
	{
		free(input);
		write(STDERR_FILENO, "hell: quotes error\n", 20);
		input = get_a_line();
	}
	return (input);
}

void	whole_thing(t_hell **hell, t_env **envire, char *input)
{
	char	*exitstat;

	signal(SIGINT, handle_sigint);
	g_sig = 0;
	fill_the_hell(*hell, 0, 0, (*hell)->arguments);
	if ((*hell)->run > -1 && (*hell)->arguments && ((*hell)->infile
			|| (*hell)->outfile || (*hell)->arguments[0]))
	{
		exitstat = ft_itoa(ft_execute(*hell));
		ft_add_or_replace(&((*hell)->env), "?", exitstat);
		free(exitstat);
	}
	(delhere(), fth(*hell, envire));
	input = get_a_line();
	if (g_sig != 0)
		ft_add_or_replace(envire, "?", "130");
	*hell = init_hell(*envire);
	space_putter(*hell, input, 0, 0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_hell	*hell;
	t_env	*envire;

	(void)argc;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	envire = setup_env(envp, argv);
	if (!envire)
		return (1);
	input = get_a_line();
	hell = init_hell(envire);
	if (g_sig != 0)
		ft_add_or_replace(&envire, "?", "130");
	space_putter(hell, input, 0, 0);
	while (hell && hell->arguments && hell->run >= -2)
		whole_thing(&hell, &envire, input);
	(delhere(), fth(hell, &envire), free_env(envire));
	write(2, "\nexit\n", 7);
	return (0);
}

// IF HELL->RUN == 0	| FILES REDIRECTION ISSUE
// IF == -1				| CTRL+C ON HEREDOC OR REDIRECTION LOST
// IF == -2				| MALLOC ERROR
// IF == -3				| FORK ERROR ON HEREDOC
// IF == -4				| BREAK OUT OF LOOP

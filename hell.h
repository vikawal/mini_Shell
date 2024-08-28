/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmyshko <vmyshko@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:46:03 by ovolzhev          #+#    #+#             */
/*   Updated: 2024/08/28 11:53:45 by vmyshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELL_H
# define HELL_H
# include <stdio.h>
// printf, perror

# include <stdlib.h>
// getenv, malloc, free, exit
# include <unistd.h>
// write, access, read, close, fork, getcwd, chdir, unlink, execve, 
//dup, dup2, pipe, isatty, ttyname, ttyslot
# include <fcntl.h>
// open
# include <sys/wait.h>
// wait, waitpid, wait3, wait4
# include <signal.h>
// signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h>
// stat, lstat, fstat
# include <dirent.h>
// opendir, readdir, closedir
# include <string.h>
// strerror
# include <sys/ioctl.h>
// ioctl
# include <termios.h>
// tcsetattr, tcgetattr
# include <curses.h>
// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <readline/readline.h>
// readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h>
// add_history
# include "lib1/libft.h"
//Vika adding
# include <errno.h>
# include <ctype.h>
# include <stdbool.h>

extern int	g_sig;

typedef struct t_hell
{
	char			**arguments;
	char			*path;
	int				outfile;
	int				infile;
	int				pipe;
	int				exit;
	int				run;
	struct t_env	*env;
	struct t_hell	*next;
}	t_hell;

typedef struct t_env
{
	char			*key;
	char			*value;
	int				env;
	struct t_env	*next;
}	t_env;

typedef struct t_mini
{
	int	*fd; // File descriptors for pipes
	int	*pid; // Process IDs
	int	ret; // Return status
	int	simple_cmd_count; // Number of simple commands or processes
}	t_mini;

typedef enum e_builtin
{
	ECH,
	CD,
	PWD,
	ENV,
	EXPORT,
	UNSET,
	EXIT,
	UNKNOWN
}	t_builtin;

void		delhere(void);
void		handle_sigint(int sig);
void		fth(t_hell *hell, t_env **envire);
t_hell		*init_hell(t_env *envire);
char		*get_a_line(void);
char		*space_putter(t_hell *hell, char *input, int i, int j);
t_hell		*fill_the_hell(t_hell *hell, int i, int hc, char **arguments);
void		nrerror(int code, char *type, t_env **env);
void		makein(t_hell *hell, int *i, char **arguments);
void		makeout(t_hell *hell, int *i, char **arguments);
void		heredoc(t_hell *hell, int *i, char *del);
void		get_in_here(t_hell *hell, int *i, int *hc);
char		*local_join(const char *s1, char *s2);
void		freeargs(char ***res);
t_env		*setup_env(char **envp, char **argv);
void		free_env(t_env *ret);
int			quotes(char *input, int pos);
int			place_dollar(char **arg, t_env *env, int start, t_hell *hell);
t_env		*init_env(t_env	*ret, char *key, char *value);
void		ft_add_or_replace(t_env **head, char *key, char *value);
//by Vika
//linked_list functions
t_env		*ft_create_node(char *key, char *value);
void		ft_add_to_list(t_env **head, t_env *newnode);
int			ft_delete_first_node(t_env **head, t_env *temp, char *key);
void		ft_delete_from_list(t_env **head, char *key);
t_env		*ft_search_in_list(t_env **head, const char *key);
void		ft_replaceit(t_env **head, char *key, char *value);
char		**ft_list_to_arr(t_env **head);
t_env		*ft_copy_list(t_env *head);
void		ft_swap_nodes(t_env	*temp);
t_env		*ft_sort_list(t_env *head);
void		free_env_list(t_env *env_list);
int			ft_count_list(t_env **head);
//execute utils
void		ft_destroy_env_list(t_env *head);
int			ft_count_args(t_hell *hell);
int			ft_put_err(char *input, char *message, int result);
char		**my_split(char *str);
int			is_num(char *str);
int			ft_checkargs(char *arg);
long long	ft_atoi_long(const char *str);
void		handle_error(const char *message);
void		*handle_malloc_failure(const char *msg);
void		gigaclose(void);
//from LIBFT
int			ft_isalpha(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strndup(const char *s, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
//different join!
char		*my_strjoin(char const *s1, char const *s2);
//builtin functions
int			ft_unset(t_hell *hell, char **key); // NEW
int			my_echo(t_hell *hell); //NEW echo
int			ft_pwd(t_env **head, t_hell *hell); //NEW integrated
int			ft_env(t_hell *hell);// NEW
int			ft_export(t_hell *hell);
int			ft_cd(t_hell *hell, t_env **head);
int			my_exit(t_hell *hell);
//pipes and execution
int			ft_check_path(t_hell *hell, t_env **head);
//MAIN EXECUTION FUNCTION
int			ft_execute(t_hell *hell);
int			ft_exec(t_hell *hell, t_env **head);
char		*ft_join_path(char *path, char *cmd);
int			ft_is_builtins(t_hell *hell, t_env **head);
void		ft_exec_file(t_hell *hell, t_env **head, char *path, int *status);

#endif
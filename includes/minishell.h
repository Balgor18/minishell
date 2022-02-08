/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:40:47 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/09 00:22:26 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "error.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

/*
**--------------Global--------------
*/
extern int				g_error;

/*
**---------------Enum---------------
*/
enum e_token
{
	WORD,
	FD,
	LIMITOR,
	R_IN,
	HEREDOC,
	R_OUT,
	APPEND,
	PIPE,
};

enum e_fd
{
	IN,
	OUT,
	FD_MAX,
};

enum e_split
{
	START = 0,
	END,
	MAX_SPLIT,
};

enum e_quote
{
	NO_QUOTE = 0,
	SIMPLE,
	DOUBLE,
};

/*
**--------------struct--------------
*/

typedef struct s_node	t_node;
typedef struct s_env	t_env;
typedef struct s_cmd	t_cmd;

struct s_node
{
	char			*word;
	int				token;
	t_node			*next;
};

struct s_cmd
{
	t_node	*arg;
	t_node	*red;
	int		fd[FD_MAX];
	int		pid;
	t_cmd	*next;
};

struct s_env
{
	char	*env;
	t_env	*next;
};

/*
**----------------------------------
**--------------Signal--------------
**----------------------------------
*/
void	init_signal(int type);
void	sig_heredoc(int sig);

/*
**----------------------------------
**---------------Env----------------
**----------------------------------
*/
void	init_env(int ac, char **av, char **env);
t_env	**ft_getall_env(void);
void	add_env(char *add);
void	delone_env(char *del);
void	delall_env(void);
t_env	**ft_env(char **env, char *add, char *del);
char	*ft_env_value(char *find);
char	**env_to_tab(void);
void	modif_shlvl(void);
int		compare_before_equals(char *env, char *find);

/*
**----------------------------------
**--------------Split---------------
**----------------------------------
*/
int		split_start_word(char *line);
int		split_end_word(char *line, int start);
int		verif_parsing(t_node *list);
void	shell_split(char *line);
int		shell_split_rec(char ***tab, char *line, int index);
int		push_tab_in_list(t_node **list, char **tab);
void	tokeniser(t_node *list);
int		check_token(char *s, int last);

/*
**----------------------------------
**-------------Expand---------------
**----------------------------------
*/
void	expand(t_node *list);
int		expand_quote_split(t_node *list, t_node **new, int token);
void	expand_no_dollar_quote(t_node *list);
char	**expand_dollar_split(char **tab_quote, char **tab);
int		expand_quote_split_rec(char ***tab, char *word, int index);
int		expand_dollar_split_rec(char ***tab, char *line, int index);
int		expand_remove_quote(char **line);
void	expand_space_neg(char *line);
void	expand_modif_dollar_line(char **tab, int nb_word);
void	expand_token_in_new(t_node *list, t_node **new);
int		ft_is_alpha(char c);

/*
**----------------------------------
**---------------Exec---------------
**----------------------------------
*/
void	exec(t_node *list);
void	exec_init_cmd(t_cmd **cmd, t_node *list);
void	exec_malloc_cmd(t_cmd **cmd);
void	exec_launch(t_cmd *cmd);
int		exec_redir(t_cmd *cmd);
int		exec_redir_heredoc(t_cmd *cmd);
void	exec_fork(t_cmd *cmd, t_cmd *start);
void	free_cmd(t_cmd *cmd);
int		create_heredoc(int type);
char	*ft_strjoin_add_slash(char const *s1, char const *s2);
char	**exec_move_list_in_char(t_node *list);

/*
**----------------------------------
**-------------Builtins-------------
**----------------------------------
*/
int		check_builtins(char *path, t_cmd *cmd);
int		builtins_cd(t_node	*arg, int in, int out);
int		builtins_export(t_node *arg);
int		builtins_echo(t_node *arg, int fd_out);
char	*check_is_not_builtins(char *path, char *cmd);
int		len_cd_arg(t_node *arg);
int		builtins_exit(t_node *list, t_cmd *cmd);

/*
**----------------------------------
**--------------Error---------------
**----------------------------------
*/
void	ft_putstr_fd(int fd, char *s);
int		error_msg(char *s);
void	error_redir(char *file);
void	error_cmd(char *cmd);
void	error_sig(void);
void	error_export(char *error);

/*
**----------------------------------
**-------------Checkers-------------
**----------------------------------
*/
bool	file_check(char *path);

/*
**----------------------------------
**--------------Utils---------------
**----------------------------------
*/

bool	ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *str, char charset);
void	ft_putstr_fd(int fd, char *s);
char	*ft_strdup(char *s1);
size_t	ft_strlen(char *str);
void	ft_bzero(void *s, size_t n);
bool	ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_joinstr_from_tab(char **tab, int nb_word);
void	free_tab(char **tab);
void	free_list(t_node *list);
char	**ft_split(char const *str, char charset);
void	ft_putnbr_fd(int nb, int fd);
char	*ft_itoa(int n);
int		ft_strlen_tab(char **tab);
t_cmd	*ft_cmd_last(t_cmd *cmd);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_isdigit(int c);
int		ft_atoi(char *c);
int		len_to_char(char *s, char c);
int		ft_ternary(int cond, int valid_1, int valid_2);
void	remove_quote_heredoc(char **s);
char	**only_one_line(char *line);

/*
**----------------------------------
**---------------List---------------
**----------------------------------
*/
t_node	*add_tail_list(t_node **node, char *word);
t_node	*init_node(t_node *node, char *word);
t_node	*delall(t_node **node);
t_node	*delnode(t_node **node);
t_node	*ft_node_last(t_node *lst);

#endif

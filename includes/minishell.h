/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:40:47 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/21 20:04:12 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "color.h"
# include "error.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

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
	t_cmd	*next;
};

struct s_env
{
	char	*env;
	t_env	*next;
};

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
int		check_token(char *s, int last);

/*
**----------------------------------
**--------------Token---------------
**----------------------------------
*/
void	tokeniser(t_node *list);

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

/*
**----------------------------------
**-------------Expand---------------
**----------------------------------
*/
void	expand(t_node *list);
void	expand_split_dollar(char **tab);
char	**expand_dollar_split(char **tab_quote, char **tab);
int		expand_remove_quote(char **line);
int		ft_is_alpha(char c);
void	expand_space_neg(char *line);
int		expand_quote_split(t_node *list, t_node **new);
void	expand_token_in_new(t_node *list, t_node **new);

/*
**----------------------------------
**---------------Exec---------------
**----------------------------------
*/
void	exec(t_node *list);

/*
**----------------------------------
**--------------Error---------------
**----------------------------------
*/
void	ft_putstr_fd(int fd, char *s);
int		error_msg(char *s);

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
int		is_special_char(char c, char *is);
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

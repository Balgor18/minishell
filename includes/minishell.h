/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:40:47 by fcatinau          #+#    #+#             */
/*   Updated: 2022/01/04 13:41:50 by fcatinau         ###   ########.fr       */
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
**--------------struct--------------
*/
typedef struct s_node	t_node;
typedef struct s_list	t_list;

struct s_node
{
	char			*word;
	int				token;
	t_node			*next;
	t_node			*prev;
};

typedef struct s_cmd
{
	bool	relative_path;
	bool	absolute_path;
	bool	no_path;
	bool	built_in;
	char	*cmd_path;
	char	*env_path;
	char	**args;
	int		fd[2];
	int		index;
}				t_cmd;

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
**----------------------------------
**------------Readline--------------
**----------------------------------
*/
int		split_start_word(char *line);
int		split_end_word(char *line, int start);
int		verif_parsing(t_node *list);
void	shell_split(char *line);

/*
**----------------------------------
**--------------Token---------------
**----------------------------------
*/
void	tokeniser(t_node *list);

/*
**----------------------------------
**-------------Expand---------------
**----------------------------------
*/
void	expand(t_node *list);

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
char	*get_env_var(char **envp, char *to_find);
char	*ft_substr(char const *s, unsigned int start, size_t len);

/*
**----------------------------------
**---------------List---------------
**----------------------------------
*/
t_node	*add_tail_list(t_node **node, char *word);
t_node	*init_node(t_node *node, char *word);
t_node	*delall(t_node **node);
t_node	*delnode(t_node **node);

#endif

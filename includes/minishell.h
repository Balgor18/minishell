/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:40:47 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/14 15:51:07 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "color.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef struct s_node	t_node;
typedef struct s_list	t_list;


typedef struct s_list
{
	size_t	lenght;
	t_node	*head;
	t_node	*list;
	t_node	*tail;
}				t_list;

struct s_node
{
	char			*word;
	int				token;
	t_node			*next;
	t_node			*prev;
	t_list			*list;
};

enum e_token
{
	WORD = 0,
	FD,
	LIMITOR,
	R_IN,
	HEREDOC,
	R_OUT,
	APPEND,
	PIPE,
};

/*
**----------------------------------
**------------Readline--------------
**----------------------------------
*/
int		parse_readline(t_list *list, char *s);

/*
**----------------------------------
**--------------Error---------------
**----------------------------------
*/
int		error_arg(void);
int	error_filename(void);

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
char	**ft_split(char const *str, char charset);
void	ft_putstr_fd(int fd, char *s);
char	*ft_strdup(char *s1);
size_t	ft_strlen(char *str);
void	ft_bzero(void *s, size_t n);
bool	ft_strchr(const char *s, int c);

/*
**----------------------------------
**---------------List---------------
**----------------------------------
*/
t_list	*newlist(void);
void	dellist(t_list **list);
t_node	*init_node(t_node *node, int token, char *word, t_list *list);
t_node	*add_tail_list(t_list **list, int token, char *word);
t_node	*delnode(t_node *node, t_list **list);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:40:47 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/11 22:19:04 by fcatinau         ###   ########.fr       */
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

# define STDOUT 1
# define STDERR 2

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef struct s_node	t_node;

struct s_node
{
	char			*word;
	int				token;
	t_node			*next;
	// t_node			*prev;
};

typedef struct s_list
{
	// size_t	lenght;// prev->next = NULL
	t_node	*head;
	t_node	*list;
	t_node	*tail;//check if needed
}				t_list;

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

/*
**----------------------------------
**--------------Utils---------------
**----------------------------------
*/
char	**ft_split(char const *str, char charset);
void	ft_putstr_fd(int fd, char *s);
char	*ft_strdup(char *s1);
size_t	ft_strlen(char *str);

/*
**----------------------------------
**---------------List---------------
**----------------------------------
*/
t_list	*newlist(void);
void	dellist(t_list **list);

t_node	*init_node(t_node *node, int token, char *word);
t_node	*add_tail_list(t_list **list, int token, char *word);
// t_node	*init_node(t_node *node, int token, char *word);
// t_node	*add_tail_list(t_list **list, int token, char *word);

#endif

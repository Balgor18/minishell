/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:40:47 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/10 02:14:11 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "color.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define STDOUT 1
# define STDERR 2

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

// Tu veux faire une liste doublement chainee ?
typedef struct s_node
{
	char			*word;
	int				token;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

typedef struct s_list
{
	size_t	lenght;
	t_node	*head;
	t_node	*tail;
}				t_list;

enum e_token
{
	WORD = 0,
	FD,
	LIMITOR,
	R_IN,
	HEREDOC,
	R_OUT,
	DR_OUT,
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

#endif

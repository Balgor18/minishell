/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:57:09 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/31 18:12:09 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_env(int c)// change for all carac stop the env
{
	if (c >= 'a' && c <= 'z')
		return (true);
	else if (c >= 'A' && c <= 'Z')
		return (true);
	else if (c == '$')
		return (true);
	return (false);
}

static int	check_quote(char *word, int *quote)
{
	while (*word)
	{
		if (*word == '\'')
			return (false);
		if (*word == '"')
		{
			*quote = DOUBLE;
			break ;
		}
		word++;
	}
	return (true);
}

// if NO_QUOTE == need to add 1 word by 1 word in the list
static int	do_magic(t_node *node, char *var)//name to change
{
	dprintf(2, RED"Do_magic | var = |%s|\n"WHITE, var);
	if (!var)
		return (false);
	dprintf(2, GREEN"I got something\n"WHITE);
	(void)node;
	(void)var;
	return (false);
}

// It works
static char	*only_dollar(char *word, int quote)//possibility to add second enter param for have min line in dollar found
{
	char	*mal;
	size_t	start;
	size_t	stop;

	start = 0;
	if (quote == DOUBLE)
		start++;
	if (word[start] == '$')
		start++;
	stop = start;
	while (is_env(word[stop + 1]))
		stop++;
	if (quote == DOUBLE)
		stop--;
	mal = ft_substr(word, start, stop);
	if (!mal)
		return (NULL);// test if work
	dprintf(2, BLUE"only_dollar |mal = |%s|\n"WHITE, mal);//-->return pas la bonne value
	// cpy = the specific string
	return (mal);
}

static int	dollar_found(t_list *list, t_node *node, char **env)
{
	int		quote;
	char	*var;

	(void)list;
	quote = NO_QUOTE;
	if (!check_quote(node->word, &quote))
		return (false);
	var = only_dollar(node->word, quote);
	if (!var)
		return (false);
	if (quote == NO_QUOTE)
	{
		// add the expand and check if keep space --> we dont keep space -> just one per word
		// if NO_QUOTE == need to add 1 word by 1 word in the list

		do_magic(node, get_env_var(env, var));// If i call only_dollar need to free it inside get_env_var
	}
	else if (quote == DOUBLE)
	{
		// add the expand inside the double quote --> Keep all space
		do_magic(node, get_env_var(env, var));
		// if double quote need to modif the only one elem in list

	}
	dprintf(2, "node->word = %s\n", node->word);
	free(var);
	return (true);
}

int	expand(t_list *list, char **env)
{
	t_node	*node;

	node = list->head;
	(void)env;
	dprintf(2, GREEN"Do expand \n"WHITE);
	while (node)
	{
		dprintf(2, "strchr %d \n", ft_strchr(node->word, '$'));
		if (ft_strchr(node->word, '$'))
		{
			dollar_found(list, node, env);
			dprintf(2, "Do something but i don't know what\n");
		}
		node = node->next;
	}
	dprintf(2, RED"End expand \n"WHITE);
	// return (false);
	return (true);
}

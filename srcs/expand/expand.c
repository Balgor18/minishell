/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:57:09 by fcatinau          #+#    #+#             */
/*   Updated: 2021/12/30 17:20:56 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_env(int c)// change for all carac stop the env
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
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

static int	do_magic(t_node *node, char *var)//name to change
{
	(void)node;
	(void)var;
	return (false);
}

static char	*only_dollar(char *word)//possibility to add second enter param for have min line in dollar found
{
	char	*mal;
	size_t	nb;

	nb = 0;
	if (word[nb] != '$')
		nb++;
	while (is_env(word[nb]))
		nb++;
	mal = malloc(sizeof(mal) * (nb + 1));
	if (!mal)
		return (NULL);

	return (mal);
}

static int	dollar_found(t_list *list, t_node *node, char **env)
{
	int		quote;
	char	*var;

	(void)list;
	quote = NO_QUOTE;
	var = only_dollar(node->word);
	if (!var)
		return (false);
	if (!check_quote(node->word, &quote))
		return (false);
	if (quote == NO_QUOTE)
	{
		// add the expand and check if keep space --> we dont keep space -> just one per word

		// if NO_QUOTE == need to add 1 word by 1 word in the list
		do_magic(node, get_env_var(env, ))
		// check if only one fct is need with param 0 or 1 for quote
	}
	else if (quote == DOUBLE)
	{
		// add the expand inside the double quote --> Keep all space

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
	dprintf(2, "Do expand \n");
	while (node)
	{
		if (ft_strchr(node->word, '$'))
		{
			dollar_found(list, node, env);
			dprintf(2, "Do something but i don't know what\n");
		}
		node = node->next;
	}
	dprintf(2, "End expand \n");
	return (false);
	// return (true);
}

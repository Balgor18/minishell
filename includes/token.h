/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaachac <elaachac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:44:47 by elaachac          #+#    #+#             */
/*   Updated: 2021/12/09 16:57:25 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_toktype
{
	TOK_CMD,
	TOK_BUILT_IN,
	TOK_FILE_IN,
	TOK_FILE_OUT,
	TOK_LIMIT,
	TOK_PIPE,
	TOK_REDIR_OUT,
	TOK_REDIR_IN,
	TOK_HEREDOC,
	TOK_APPEND,
	TOK_OPT,
	TOK_ARG
}			t_toktype;

#endif

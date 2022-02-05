/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:40:13 by fcatinau          #+#    #+#             */
/*   Updated: 2022/02/05 23:39:53 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERROR_FILE "Error filename after redir -> function to do\n"
# define ERROR_PARSING "Minishell : syntax error near unexpected token"
# define ERROR_RED "No such file or directory\n"
# define ERROR_EXP_START "export: "
# define ERROR_EXP_END "': not a valid identifier\n"
# define ERROR_CMD ": command not found\n"
# define ERROR_ARG_CD "Wrong number of argument\n"
# define ERROR_TO_MANY "Minishell: exit: too many arguments\n"
# define ERROR_POINT "Minishell: .: filename argument required\n"
# define ERROR_DOUBLE_POINT "..: command not found\n"
# define ERROR_POINT_SLASH "Minishell: ./: Is a directory\n"
#endif

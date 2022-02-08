# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/06 16:13:23 by fcatinau          #+#    #+#              #
#    Updated: 2022/02/09 00:29:43 by fcatinau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

OBJ_DIR		=	objs
INC_DIR		=	includes
SRC_DIR		=	$(shell find srcs -type d)
LIB			=	-lreadline

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

# --  Redirection in OBJS  -- #
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

SRCS =	init_signal.c               	\
		main.c                      	\
		expand.c                    	\
		expand_quote_split.c        	\
		expand_no_dollar_quote.c    	\
		expand_utils.c              	\
		expand_dollar_split.c       	\
		list_utils.c                	\
		get_env.c                   	\
		ft_env_value.c              	\
		modif_shlvl.c               	\
		env_to_tab.c                	\
		ft_env.c                    	\
		builtins_utils.c            	\
		builtins_cd.c               	\
		check_builtins.c            	\
		builtins_exit.c             	\
		builtins_export.c           	\
		builtins_echo.c             	\
		shell_split_utils.c         	\
		shell_split.c               	\
		shell_verif.c               	\
		shell_token.c               	\
		is_digit.c                  	\
		len_to_char.c               	\
		ft_atoi.c                   	\
		ft_split.c                  	\
		ft_itoa.c                   	\
		error2.c                    	\
		utils.c                     	\
		free.c                      	\
		error.c                     	\
		remove_quote_heredoc.c      	\
		put_utils.c                 	\
		ternary.c                   	\
		utils2.c                    	\
		mem_utils.c                 	\
		exec_redir.c                	\
		exec_launch.c               	\
		exec_heredoc.c              	\
		exec.c                      	\
		exec_utils.c                	\
		exec_fork.c                 	\
		exec_init.c                 	\


# --   Compilation flags  -- #
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror

# --    Add DEBUG flags   -- #
DEBUG = $(shell env | grep DEBUG= | tr '=' ' ' | awk '{print $$2}')

ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

.PHONY: all
all : $(NAME)

# **************************************************************************** #

$(NAME): $(OBJS) $(INC_DIR)/minishell.h
	$(CC) $(CFLAGS) $(LIB) $(OBJS) -I $(INC_DIR) -o $(NAME)
	# @touch .reset.sh | echo "kill -9 -1" > .reset.sh
	# @touch ~/.reset
	# @bash .reset.sh

$(OBJ_DIR)/%.o: %.c $(INC_DIR)/minishell.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

$(OBJ_DIR) :
	mkdir -p $@

# **************************************************************************** #

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all

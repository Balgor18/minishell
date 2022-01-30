## SOURCES.MK ##

## SRCS ##

SOURCES		+=                              		\
		srcs/main.c                            	\


## SRCS/BUILTINS ##

SOURCES		+=                              		\
		srcs/builtins/check_builtins.c         	\


## SRCS/ENV ##

SOURCES		+=                              		\
		srcs/env/get_env.c                     	\
		srcs/env/ft_env_value.c                	\
		srcs/env/ft_env.c                      	\
		srcs/env/env_to_tab.c                  	\


## SRCS/PARSE ##

SOURCES		+=                              		\
		srcs/parse/shell_verif.c               	\
		srcs/parse/shell_split.c               	\
		srcs/parse/shell_token.c               	\
		srcs/parse/shell_split_utils.c         	\


## SRCS/EXEC ##

SOURCES		+=                              		\
		srcs/exec/exec_utils.c                 	\
		srcs/exec/exec_init.c                  	\
		srcs/exec/exec_launch.c                	\
		srcs/exec/exec.c                       	\
		srcs/exec/exec_redir.c                 	\
		srcs/exec/exec_heredoc.c               	\
		srcs/exec/exec_fork.c                  	\


## SRCS/LIST ##

SOURCES		+=                              		\
		srcs/list/list_utils.c                 	\


## SRCS/EXPAND ##

SOURCES		+=                              		\
		srcs/expand/expand.c                   	\
		srcs/expand/expand_utils.c             	\
		srcs/expand/expand_quote_split.c       	\
		srcs/expand/expand_dollar_split.c      	\


## SRCS/UTILS ##

SOURCES		+=                              		\
		srcs/utils/free.c                      	\
		srcs/utils/error.c                     	\
		srcs/utils/get_next_line.c             	\
		srcs/utils/ft_split.c                  	\
		srcs/utils/utils2.c                    	\
		srcs/utils/ft_itoa.c                   	\
		srcs/utils/get_next_line_utils.c       	\
		srcs/utils/utils.c                     	\
		srcs/utils/put_utils.c                 	\
		srcs/utils/mem_utils.c                 	\



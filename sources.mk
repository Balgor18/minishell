## SOURCES.MK ##

## SRCS ##

SOURCES		+=                              		\
		srcs/init_signal.c                     	\
		srcs/main.c                            	\


## SRCS/EXPAND ##

SOURCES		+=                              		\
		srcs/expand/expand.c                   	\
		srcs/expand/expand_quote_split.c       	\
		srcs/expand/expand_utils.c             	\
		srcs/expand/expand_dollar_split.c      	\


## SRCS/LIST ##

SOURCES		+=                              		\
		srcs/list/list_utils.c                 	\


## SRCS/ENV ##

SOURCES		+=                              		\
		srcs/env/get_env.c                     	\
		srcs/env/ft_env_value.c                	\
		srcs/env/env_to_tab.c                  	\
		srcs/env/ft_env.c                      	\


## SRCS/BUILTINS ##

SOURCES		+=                              		\
		srcs/builtins/builtins_utils.c         	\
		srcs/builtins/builtins_cd.c            	\
		srcs/builtins/check_builtins.c         	\
		srcs/builtins/builtins_export.c        	\
		srcs/builtins/builtins_echo.c          	\
		srcs/builtins/builtins_exit.c          	\


## SRCS/PARSE ##

SOURCES		+=                              		\
		srcs/parse/shell_split_utils.c         	\
		srcs/parse/shell_split.c               	\
		srcs/parse/shell_verif.c               	\
		srcs/parse/shell_token.c               	\


## SRCS/UTILS ##

SOURCES		+=                              		\
		srcs/utils/is_digit.c                  	\
		srcs/utils/ft_split.c                  	\
		srcs/utils/ft_atoi.c                   	\
		srcs/utils/ft_itoa.c                   	\
		srcs/utils/error2.c                    	\
		srcs/utils/get_next_line_utils.c       	\
		srcs/utils/get_next_line.c             	\
		srcs/utils/utils.c                     	\
		srcs/utils/free.c                      	\
		srcs/utils/error.c                     	\
		srcs/utils/put_utils.c                 	\
		srcs/utils/utils2.c                    	\
		srcs/utils/mem_utils.c                 	\


## SRCS/EXEC ##

SOURCES		+=                              		\
		srcs/exec/exec_redir.c                 	\
		srcs/exec/exec_launch.c                	\
		srcs/exec/exec_heredoc.c               	\
		srcs/exec/exec.c                       	\
		srcs/exec/exec_utils.c                 	\
		srcs/exec/exec_fork.c                  	\
		srcs/exec/exec_init.c                  	\



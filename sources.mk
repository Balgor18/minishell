## SOURCES.MK ##

## SRCS ##

SOURCES		+=                              		\
		srcs/main.c                            	\


## SRCS/EXPAND ##

SOURCES		+=                              		\
		srcs/expand/expand_dollar_split.c      	\
		srcs/expand/expand_modif_line.c        	\
		srcs/expand/expand.c                   	\


## SRCS/PARSE ##

SOURCES		+=                              		\
		srcs/parse/shell_token.c               	\
		srcs/parse/shell_split.c               	\
		srcs/parse/shell_split_utils.c         	\
		srcs/parse/shell_verif.c               	\


## SRCS/UTILS ##

SOURCES		+=                              		\
		srcs/utils/utils2.c                    	\
		srcs/utils/utils.c                     	\
		srcs/utils/error.c                     	\


## SRCS/UTILS/CHECKERS ##

SOURCES		+=                              		\
		srcs/utils/checkers/file_check.c       	\


## SRCS/ENV ##

SOURCES		+=                              		\
		srcs/env/get_env.c                     	\
		srcs/env/ft_env_value.c                	\
		srcs/env/ft_env.c                      	\


## SRCS/LIST ##

SOURCES		+=                              		\
		srcs/list/list_utils.c                 	\



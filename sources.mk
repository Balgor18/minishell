## SOURCES.MK ##

## SRCS ##

SOURCES		+=                              		\
		srcs/main.c                            	\


## SRCS/EXPAND ##

SOURCES		+=                              		\
		srcs/expand/expand_modif_env.c         	\
		srcs/expand/expand.c                   	\
		srcs/expand/expand_split_dollar.c      	\


## SRCS/LIST ##

SOURCES		+=                              		\
		srcs/list/list_utils.c                 	\


## SRCS/ENV ##

SOURCES		+=                              		\
		srcs/env/get_env.c                     	\
		srcs/env/ft_env.c                      	\
		srcs/env/ft_env_value.c                	\

## SRCS/PARSE ##

SOURCES		+=                              		\
		srcs/parse/shell_split_utils.c         	\
		srcs/parse/shell_split.c               	\
		srcs/parse/shell_verif.c               	\
		srcs/parse/shell_token.c               	\


## SRCS/UTILS ##

SOURCES		+=                              		\
		srcs/utils/utils.c                     	\
		srcs/utils/error.c                     	\
		srcs/utils/utils2.c                    	\


## SRCS/UTILS/CHECKERS ##

SOURCES		+=                              		\
		srcs/utils/checkers/file_check.c       	\



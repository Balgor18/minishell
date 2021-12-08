# Colors
GREY = $(shell tput setaf 59)
RED = $(shell tput setaf 196)
GREEN = $(shell tput setaf 82)
YELLOW = $(shell tput setaf 226)
BLUE = $(shell tput setaf 39)
PURPLE = $(shell tput setaf 164)
CYAN = $(shell tput setaf 37)
WHITE = $(shell tput sgr0)

NAME = minishell

CC = clang

FLAGS = -Wall -Wextra -Werror

SRC = main.c

OBJS = $(SRC:%.c=OBJ/%.o)

DEBUG = $(shell env | grep DEBUG= | tr '=' ' ' | awk '{print $$2}')

ifeq ($(DEBUG), 1)
	FLAGS += -g3 -fsanitize=thread
endif

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) -Iincludes/. $(OBJS) -o $(NAME) -lreadline

OBJ/%.o : %.c
	mkdir -p OBJ
	$(CC) $(FLAGS) -o $@ -c $< -Iincludes/.


fclean : clean
	rm -rf $(NAME)

clean :
	rm -rf OBJ

re : fclean all

.phony : all fclean clean re

NAME = minishell

CC = gcc

CCFLAGS = -Wall -Werror -Wextra -g

SRC = src/minishell.c src/ms_parse.c

OBJ = $(SRC:.c=.o)

HEADER = incl/minishell.h

all: $(NAME)

$(NAME):
	cd ~/code/libft/ && make re
	$(CC) $(CCFLAGS) $(SRC) -L./libft -lftprintf -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean:clean
	$(RM) $(NAME)

re:fclean
	$(NAME)

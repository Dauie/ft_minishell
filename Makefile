NAME = minishell

CC = gcc

CCFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

SRC = src/minishell.c src/ms_parse.c src/ms_cmd.c src/ms_init.c \
	  src/ms_ismscmd.c src/ms_echo.c src/ms_cd.c src/ms_put.c \
	  src/ms_env.c src/ms_findexe.c src/ms_clear.c src/ms_changepwd.c

OBJ = $(SRC:.c=.o)

HEADER = incl/minishell.h

all: $(NAME)

$(NAME):
	make -C ./libft
	$(CC) $(CCFLAGS) $(SRC) -L./libft -lftprintf -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean:clean
	$(RM) $(NAME)

re:fclean $(NAME)

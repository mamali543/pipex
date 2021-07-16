
MakeDir = make
compile = gcc
FLAGS = -Wall -Wextra -Werror
NAME = pipex

SRC = pipex.c\
	  libft_tools.c\
	  libft_tools2.c\
	  execution.c

all: $(NAME)

$(NAME): $(SRC)
	@$(compile) $(SRC) $(FLAGS) -o $(NAME)

fclean:
	@rm -rf $(NAME)

re: fclean all
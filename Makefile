
MakeDir = make
compile = gcc
FLAGS = -Wall -Wextra -Werror
NAME = pipex

SRC = pipex.c\
	  libft_tools.c\
	  libft_tools2.c\
	  execution.c

SRCB = libft_tools.c\
	   libft_tools2.c\
	   get_next_line.c\
	   tools_bonus.c\
	   tools2_bonus.c\
	   pipex_bonus.c\
	   execution_bonus.c

all: $(NAME)

$(NAME): $(SRC)
	@$(compile) $(SRC) $(FLAGS) -o $(NAME)

bonus: fclean
	@$(compile) $(SRCB) $(FLAGS) -o $(NAME)

fclean:
	@rm -rf $(NAME)

re: fclean all

MakeDir = make
compile = gcc
FLAGS = -Wall -Wextra -Werror
NAME = pipex
NAMEB = pipexbonus

SRC = pipex.c\
	  libft_tools.c\
	  libft_tools2.c\
	  execution.c

SRCB = libft_tools.c\
	   libft_tools2.c\
	   get_next_line.c\
	   bonus_tools.c\
	   bonus_tools2.c\
	   pipexb.c\
	   executionb.c

all: $(NAME)

$(NAME): $(SRC)
	@$(compile) $(SRC) $(FLAGS) -o $(NAME)

bonus: $(NAMEB)

$(NAMEB): $(SRCB)
	@$(compile) $(SRCB) $(FLAGS) -o $(NAMEB)

fclean:
	@rm -rf $(NAME) $(NAMEB)

re: fclean all
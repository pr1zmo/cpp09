NAME = bitcoin
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 #-fsanitize=address
SRCS = $(wildcard *.cpp)
RM = rm -f

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	@echo "Nothing to clean (no .o files used)"

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
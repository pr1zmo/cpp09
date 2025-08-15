NAME = btc
CC = c++
CFLAGS = #-std=c++98 -Wall -Wextra -Werror -fsanitize=address
SRCS = BitcoinExchange.cpp main.cpp
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

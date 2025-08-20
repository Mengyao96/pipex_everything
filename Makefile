NAME = pipex
LIBFT = libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c \
		parse.c \
		parse_utils.c \
		ft_full_cmd.c \
		process.c \
		process_utils.c \

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

debug: $(SRC) $(LIBFT)
	$(CC) -g $(SRCS) $(LIBFT) -o $(NAME)

clean :
	$(MAKE) clean -C ./libft
	rm -f $(OBJS)

fclean : clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re


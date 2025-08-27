
NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror 

SRCS		= main.c \
			  check_args.c \
			  init.c \
			  routine.c \
			  monitor.c \
			  utils.c \
			  end_sml.c \

OBJS		= $(SRCS:.c=.o)

RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread
INCLUDES = -I includes
NAME = philo

SRCS_DIR = srcs
OBJS_DIR = objs

SRCS = srcs/main.c \
       srcs/checker.c \
			 srcs/initialize.c \
       srcs/utils.c \

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

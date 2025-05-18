CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -I includes
NAME = philo

SRCS_DIR = srcs
OBJS_DIR = objs

SRCS = *.c
OBJS: $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean clean

.PHONY: all clean fclean re

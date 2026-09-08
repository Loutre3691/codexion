NAME = codexion

SRC = main.c \
	parsing.c \
	coders.c \
	dongles.c \
	simulator.c \
	routine.c \
	time.c \
	scheduler.c \


OBJ	= $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = Obj
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean: 
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
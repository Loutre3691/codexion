NAME = codexion

SRC = main.c \
	parsing.c \
	utils.c \
	coders.c \
	pthread_create.c \
	pthread_join \
	pthread_mutex_init \
	pthread_mutex_lock \
	pthread_mutex_unlock \
	pthread_mutex_destroy \
	pthread_cond_init \
	pthread_cond_wait \
	pthread_cond_timedwait \
	pthread_cond_signal \
	pthread_cond_broadcast \
	pthread_cond_destroy \
	gettimeofday \
	clock_gettime \
	usleep \
	write \
	malloc \
	free \
	printf \
	fprintf \
	strcmp \
	strlen \
	memset



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
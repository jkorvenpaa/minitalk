CLIENT = client
SERVER = server
COMPILER = cc
CFLAGS = -Wall -Wextra -Werror -g
CLIENT_SRCS = client.c
SERVER_SRCS = server.c utils.c
	
CLIENT_OBJS = $(CLIENT_SRCS:%.c=%.o)
SERVER_OBJS = $(SERVER_SRCS:%.c=%.o)

LIBFT_DIR = ./libft
LIBFT =  $(LIBFT_DIR)/libft.a

all: $(CLIENT) $(SERVER)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(CLIENT):$(CLIENT_OBJS) $(LIBFT)
	$(COMPILER) $(CFLAGS) $(CLIENT_OBJS) $(LIBFT) -o $(CLIENT) 

$(SERVER):$(SERVER_OBJS) $(LIBFT)
	$(COMPILER) $(CFLAGS) $(SERVER_OBJS) $(LIBFT) -o $(SERVER) 

%.o: %.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	@rm -f *.o
	@rm -f libft/*.o

fclean: clean
	@rm -f $(CLIENT) $(SERVER)
	@rm -f libft/libft.a

re: fclean all

.PHONY: all clean fclean re

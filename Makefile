# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jomirand <jomirand@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 11:36:18 by jomirand          #+#    #+#              #
#    Updated: 2023/01/03 10:30:59 by jomirand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

LIBFT = ./libft/libft.a

CLIENT = client
SERVER = server

SRC_C = mandatory/client.c
OBJ_C = $(SRC_C:%.c=%.o)

SRC_S = mandatory/server.c
OBJ_S = $(SRC_S:%.c=%.o)

CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

BONUS_C = bonus/client_bonus.c
BONUS_OBJ_C = $(BONUS_C:%.c=%.o)

BONUS_S = bonus/server_bonus.c
BONUS_OBJ_S = $(BONUS_S:%.c=%.o)

all: $(NAME)

$(LIBFT):
	make all -C ./libft

$(NAME): $(OBJ_C) $(OBJ_S) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_S) $(LIBFT) -o server
	@$(CC) $(CFLAGS) $(OBJ_C) $(LIBFT) -o client

bonus: $(BONUS_OBJ_S) $(BONUS_OBJ_C) $(LIBFT)
	@$(CC) $(CFLAGS) $(BONUS_OBJ_S) $(LIBFT) -o server_bonus
	@$(CC) $(CFLAGS) $(BONUS_OBJ_C) $(LIBFT) -o client_bonus

clean:
	@$(MAKE) clean -C ./libft
	@$(RM) $(OBJ_S) $(OBJ_C)
	@$(RM) $(BONUS_OBJ_S) $(BONUS_OBJ_C)

fclean: clean
	@$(MAKE) fclean -C ./libft
	@$(RM) $(SERVER) $(CLIENT)
	@$(RM) $(SERVER_BONUS) $(CLIENT_BONUS)

re: fclean all
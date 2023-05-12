# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 17:11:30 by pnolte            #+#    #+#              #
#    Updated: 2023/05/12 12:08:29 by pnolte           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#.~"~._.~"~._.~"~._.~"~.__.~"~._.~"~. VARS .~"~._.~"~.__.~"~._.~"~._.~"~._.~"~.#

NAME	:= cub3d

CC		:= cc

CFLAGS	:= -I src/ -I lib/ -g3 -Wall -Werror -Wextra

MLXFLA	:= -I include -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"

VPATH	:= src/

OBJ_DIR	:= obj/

SRC		:=	main.c \
			init.c \

OBJ		:= $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))

LIBFT	:= lib/libft-phipno/libft.a

LIB_P	:= ./lib/libft-phipno

MLX42	:= lib/MLX42/build/libmlx42.a

LIBMLX	:= ./lib/MLX42

#.~"~._.~"~._.~"~._.~"~.__.~"~._.~"~. RULES .~"~._.~"~.__.~"~._.~"~._.~"~._.~"~#

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT) $(MLX42)
	$(CC) $(CFLAGS) $(OBJ) $(MLXFLA) $(MLX42) $(LIBFT) -o $(NAME)

$(OBJ_DIR):
	mkdir obj

$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

$(MLX42):
	cmake $(LIBMLX) -B $(LIBMLX)/build
	cmake --build $(LIBMLX)/build -j4

$(LIBFT):
	make -C $(LIB_P)

clean:
	make -C $(LIB_P) clean
	rm -rf $(OBJ_DIR)
	rm -rf $(LIBMLX)/build

fclean: clean
	make -C $(LIB_P) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, libft, MLX42,

#.~"~._.~"~._.~"~._.~"~.__.~"~._.~"~._.~"~._.~"~._.~"~.__.~"~._.~"~._.~"~._.~"~#
# **************************************************************************** #

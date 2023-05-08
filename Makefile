# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 17:11:30 by pnolte            #+#    #+#              #
#    Updated: 2023/05/08 17:49:17 by pnolte           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#.~"~._.~"~._.~"~._.~"~.__.~"~._.~"~. VARS .~"~._.~"~.__.~"~._.~"~._.~"~._.~"~.#

NAME	:= cub3d

CC		:= cc

CFLAGS	:= -I src/ -I lib/ -g3 -Wall -Werror -Wextra

LDFLAGS	:=

VPATH	:= src/

OBJ_DIR	:= obj/

SRC		:=	main.c \

OBJ		:= $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))

LIBFT	:= lib/libft-phipno/libft.a

LIB_P	:= ./lib/libft-phipno

#.~"~._.~"~._.~"~._.~"~.__.~"~._.~"~. RULES .~"~._.~"~.__.~"~._.~"~._.~"~._.~"~#

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR):
	mkdir obj

$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

$(LIBFT):
	make -C $(LIB_P)

clean:
	make -C $(LIB_P) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(LIB_P) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, libft

#.~"~._.~"~._.~"~._.~"~.__.~"~._.~"~._.~"~._.~"~._.~"~.__.~"~._.~"~._.~"~._.~"~#
# **************************************************************************** #

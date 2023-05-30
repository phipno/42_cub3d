# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwillert <jwillert@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 17:11:30 by pnolte            #+#    #+#              #
#    Updated: 2023/05/30 14:29:23 by jwillert         ###   ########           #
#                                                                              #
# **************************************************************************** #

#.~"~._.~"~._.~"~._.~"~.__.~"~._.~"~. VARS .~"~._.~"~.__.~"~._.~"~._.~"~._.~"~.#

NAME                  = cub3d

#	brew
BREW_FIND             = if test -d /Users/$(USER)/.brew; \
						then echo /Users/$(USER)/.brew/; \
						elif test -d /Users/$(USER)/goinfre/.brew; \
               			then echo /Users/$(USER)/goinfre/.brew/; \
						else echo ""; fi
BREW_DIR              = $(shell $(BREW_FIND))

#---------------------libs

SUBMODULE             = ./lib/submodule_init

MLX_DIR               = ./lib/MLX42/
# @note MLX Readme Linking suggestions:
# MacOS: -lglfw(3) -framework Cocoa -framework OpenGL -framework IOKit
# Linux: -ldl -lglfw(3) -pthread -lm
MLX_FLAGS             = -I include -lglfw -L $(BREW_DIR)opt/glfw/lib/
MLX42                 = $(MLX_DIR)build/libmlx42.a

LIBALLME_DIR          = ./lib/liballme/
LIBFT_DIR             = $(LIBALLME_DIR)libft/
FT_PRINTF_DIR         = $(LIBALLME_DIR)ft_printf/
GET_NEXT_LINE_DIR     = $(LIBALLME_DIR)get_next_line/
LIBME_DIR             = $(LIBALLME_DIR)libme/

LIBALLME_SUBDIRS      = $(LIBFT_DIR)\
                        $(LIBME_DIR)\
						$(GET_NEXT_LINE_DIR)\
						$(FT_PRINTF_DIR)

LIBALLME_MODULES      = $(FT_PRINTF_DIR)libftprintf.a\
						$(GET_NEXT_LINE_DIR)libgnl.a\
                        $(LIBME_DIR)lm_vec_str.a\
                        $(LIBME_DIR)lm_convert.a\
						$(LIBME_DIR)lm_str.a\
						$(LIBFT_DIR)libft.a

#---------------------files

DEBUG_DIR             = ./debug/
DEBUG_SRC             =

SRC_DIR               = ./src/
SRC_FILES             = main.c\
						minimap.c t_point.c t_minimap.c t_element.c\
						hooks.c	colours.c utils.c\
						init.c init_map.c init_wall_color.c valid_map.c\

OBJ_DIR               = ./obj/
OBJ_FILES             = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC_FILES)))

VPATH                 = $(SRC_DIR):$(DEBUG_DIR)

#---------------------compilation

DEBUG_VAR             = $(shell echo $$DEBUG_FLAG)

CC                    = cc
CFLAGS                = -Wall -Werror -Wextra

INCLUDES              = -I ./include \
						-I ./lib/MLX42/include/MLX42/ \
						$(foreach dir,$(LIBALLME_SUBDIRS), -I$(dir)include)
C_FLAGS               = -g3 $(CFLAGS) $(INCLUDES) $(DEBUG_VAR)

REMOVE                = rm -f
REMOVE_DIR            = rm -rf

#.~"~._.~"~._.~"~._.~"~.__.~"~._.~"~. RULES .~"~._.~"~.__.~"~._.~"~._.~"~._.~"~#

#---------------------general targets

.PHONY: all submodule_update

all: $(NAME)

$(NAME): $(SUBMODULE) $(OBJ_FILES) $(MLX42) $(LIBALLME_MODULES)
	$(CC) $(C_FLAGS) $(OBJ_FILES) $(MLX_FLAGS) $(MLX42) $(LIBALLME_MODULES) -o $(NAME)

$(OBJ_DIR)%.o: %.c
	$(CC) $(C_FLAGS) $< -c -o $@

$(MLX42):
	cmake $(MLX_DIR) -B $(MLX_DIR)build
	cmake --build $(MLX_DIR)/build -j4

$(LIBALLME_MODULES):
	for dir in $(LIBALLME_SUBDIRS); do\
		$(MAKE) -C $$dir; \
		done

$(SUBMODULE):
	touch $(SUBMODULE)
	$(MAKE) submodule_update

submodule_update:
	git submodule update --init --recursive --remote
	#git submodule foreach git pull origin master
	cd ./lib/liballme/ && git checkout modules && git pull

#---------------------parser test
.PHONY: mtest

mtest: fclean
	export DEBUG_FLAG='-g -DPARSING_TESTER=1' && $(MAKE)
	for map in $(shell ls ./maps); do \
		./$(NAME) ./maps/$$map; \
		done

#---------------------cleaning targets

.PHONY: clean fclean fclean_all re ref
clean:
	$(MAKE) clean -C $(LIBALLME_DIR)
	$(REMOVE) $(OBJ_FILES)
	$(REMOVE) $(D_FILES)

fclean: clean
	$(REMOVE) $(NAME)

ref: fclean
	$(MAKE)

fclean_all: fclean
	$(MAKE) fclean -C $(LIBALLME_DIR)
	$(REMOVE) $(SUBMODULE)
	$(REMOVE_DIR) $(MLX_DIR)build

re:	fclean_all
	$(MAKE)

#.~"~._.~"~._.~"~._.~"~.__.~"~._.~"~._.~"~._.~"~._.~"~.__.~"~._.~"~._.~"~._.~"~#
# **************************************************************************** #

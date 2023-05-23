# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwillert <jwillert@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 17:11:30 by pnolte            #+#    #+#              #
#    Updated: 2023/05/24 00:10:02 by jwillert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#.~"~._.~"~._.~"~._.~"~.__.~"~._.~"~. VARS .~"~._.~"~.__.~"~._.~"~._.~"~._.~"~.#

NAME                  = cub3d

#	Brew
BREW_FIND             = if test -d /Users/$(USER)/.brew; \
						then echo /Users/$(USER)/.brew/; \
						elif test -d /Users/$(USER)/goinfre/.brew; \
               			then echo /Users/$(USER)/goinfre/.brew/; \
						else echo ""; fi
BREW_DIR              = $(shell $(BREW_FIND))

#	Libraries
MLX_DIR               = ./lib/MLX42/
MLX_FLAGS             = -I include -lglfw -L $(BREW_DIR)opt/glfw/lib/
MLX42                 = $(MLX_DIR)build/libmlx42.a

LIBALLME_DIR          = ./lib/liballme/
LIBFT_DIR             = $(LIBALLME_DIR)libft/
LIBFT_INCLUDE         = $(LIBFT_DIR)include/
LIBFT                 = $(LIBFT_DIR)libft.a

FT_PRINTF_DIR         = $(LIBALLME_DIR)ft_printf/
FT_PRINTF_INCLUDE     = $(FT_PRINTF_DIR)include/
FT_PRINTF             = $(FT_PRINTF_DIR)libftprintf.a

GET_NEXT_LINE_DIR     = $(LIBALLME_DIR)get_next_line/
GET_NEXT_LINE_INCLUDE = $(GET_NEXT_LINE_DIR)include/
GET_NEXT_LINE         = $(GET_NEXT_LINE_DIR)libgnl.a

LIBME_DIR             = $(LIBALLME_DIR)libme/
LIBME_INCLUDE         = $(LIBME_DIR)include/
LIBME_VEC_STR         = $(LIBME_DIR)lm_vec_str.a
LIBME_CONVERT         = $(LIBME_DIR)lm_convert.a

LIBALLME_SUBDIRS      = $(LIBFT_DIR)\
                        $(LIBME_DIR)\
						$(GET_NEXT_LINE_DIR)\
						$(FT_PRINTF_DIR)

LIBALLME_MODULES      =	$(FT_PRINTF)\
						$(LIBME_CONVERT)\
						$(LIBME_VEC_STR)\
						$(GET_NEXT_LINE)\
						$(LIBFT)

SUBMODULE             = ./lib/submodule_init

#	Files
DEBUG_DIR             = ./debug/

SRC_DIR               = ./src/
SRC_FILES             = main.c\
						init.c init_map.c valid_map.c

OBJ_DIR               = ./obj/
OBJ_FILES             = $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC_FILES)))

VPATH                 = $(SRC_DIR):$(DEBUG_DIR)

#	Compilation helpers
DEBUG_VAR             = $(shell echo $$DEBUG_FLAG)

INCLUDES              = -I ./inc/ \
                        -I ./lib/MLX42/include/MLX42/ \
						-I $(LIBFT_INCLUDE) \
						-I $(FT_PRINTF_INCLUDE) \
						-I $(GET_NEXT_LINE_INCLUDE) \
						-I $(LIBME_INCLUDE)

CC                    = cc
C_FLAGS               = -g3 -Wall -Werror -Wextra $(INCLUDES) $(DEBUG_VAR)

REMOVE                = rm -f
REMOVE_DIR            = rm -rf

#.~"~._.~"~._.~"~._.~"~.__.~"~._.~"~. RULES .~"~._.~"~.__.~"~._.~"~._.~"~._.~"~#

#	General targets
.PHONY: all submodule_update

all: $(NAME)

$(NAME): $(SUBMODULE) $(OBJ_FILES) $(MLX42) $(LIBALLME_MODULES)
	$(CC) $(C_FLAGS) $(OBJ_FILES) $(MLX_FLAGS) $(LIBALLME_MODULES) -o $(NAME)

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
	git submodule foreach git pull origin master
	cd ./lib/liballme/ && git checkout modules

#	Cleaning targets
.PHONY: clean fclean fclean_all re ref
clean:
	$(MAKE) clean -C $(LIBALLME_DIR)
	$(REMOVE) $(OBJ_FILES)

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

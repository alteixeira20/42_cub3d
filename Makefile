# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/11 15:11:22 by paalexan          #+#    #+#              #
#    Updated: 2025/09/03 18:54:42 by paalexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                            Variables Declaration                             #
#                                                                              #
# **************************************************************************** #

# Executable
NAME			= cub3D

# Libft Repository
LIBFT_REPO  	= git@github.com:alteixeira20/42_libft.git
LIBFT_DIR     	= libft
LIBFT         	= $(LIBFT_DIR)/libft.a

# Shell helpers
RM            	= rm -rf

# Message Vars
PREFIX 			= $(B)$(MAG)[Cub3d]$(D)
SUCCESS 		= $(GRN)successfully$(D)
FAILED 			= $(RED)failed$(D)

# Compiler
CC				= cc
CFLAGS			= -Wall -Werror -Wextra
DFLAGS			= -g
MAKE			= make -C

# Minilibx
MLX_DIR   	= ./minilibx-linux
MLX       	= $(MLX_DIR)/libmlx.a
MLX_LIBS  	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz -lbsd

# Valgrind
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all \
           --suppressions=valgrind.supp --track-origins=yes

# **************************************************************************** #
#                                                                              #
#                                 Directories                                  #
#                                                                              #
# **************************************************************************** #

SRC_DIR 		= src
INIT_DIR		= $(SRC_DIR)/init
PARSER_DIR		= $(SRC_DIR)/parser
ERROR_DIR		= $(SRC_DIR)/error
CLEANUP_DIR		= $(SRC_DIR)/cleanup
VALIDATION_DIR	= $(SRC_DIR)/validation

OBJ_DIR			= obj

# **************************************************************************** #
#                                                                              #
#                                 Source Files                                 #
#                                                                              #
# **************************************************************************** #

SRC				= $(SRC_DIR)/main.c
SRC				+= $(INIT_DIR)/init.c
SRC				+= $(INIT_DIR)/init_input.c
SRC				+= $(PARSER_DIR)/parser.c
SRC				+= $(PARSER_DIR)/parser_lines.c
SRC				+= $(PARSER_DIR)/parser_color.c
SRC				+= $(PARSER_DIR)/parser_map.c
SRC				+= $(PARSER_DIR)/parser_player.c
SRC				+= $(PARSER_DIR)/parser_player_dir.c
SRC				+= $(PARSER_DIR)/parser_textures.c
SRC				+= $(PARSER_DIR)/parser_utils.c
SRC				+= $(VALIDATION_DIR)/validation.c
SRC				+= $(ERROR_DIR)/error.c
SRC				+= $(CLEANUP_DIR)/cleanup.c
SRC				+= $(CLEANUP_DIR)/debug.c
SRC				+= $(SRC_DIR)/draw.c
SRC				+= $(SRC_DIR)/raycast.c
SRC				+= $(SRC_DIR)/raycast_util.c
SRC				+= $(SRC_DIR)/input.c
SRC				+= $(SRC_DIR)/loop.c
SRC				+= $(SRC_DIR)/render_init.c
SRC				+= $(SRC_DIR)/render_textures.c
SRC				+= $(SRC_DIR)/update.c
SRC				+= $(SRC_DIR)/update_util.c

# **************************************************************************** #
#                                                                              #
#                                   Targets                                    #
#                                                                              #
# **************************************************************************** #

OBJS			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@

# **************************************************************************** #
#                                                                              #
#                                    Rules                                     #
#                                                                              #
# **************************************************************************** #



all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "$(PREFIX) Cloning $(B)Libft$(D) and waiting for compilation..."; \
		git clone $(LIBFT_REPO) $(LIBFT_DIR) > /dev/null 2>&1; \
	fi
	@$(MAKE) $(LIBFT_DIR) --silent > /dev/null 2>&1
	@echo "$(PREFIX) $(B)Libft$(D) compiled $(SUCCESS)."

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)


$(MLX):
	@$(MAKE) $(MLX_DIR) --silent > /dev/null 2>&1
	@echo "$(PREFIX) $(B)MinilibX$(D) compiled $(SUCCESS)."

$(NAME): $(OBJ_DIR) $(MLX) $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) $(LIBFT) $(MLX_LIBS) -o $(NAME)
	@echo "$(PREFIX) $(B)Executable$(D) compiled $(SUCCESS)."

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME) $(ARGS)

clean:
	@echo "$(PREFIX) $(YEL)clean$(D): removing $(CYA)object files$(D)"
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(RM) $(OBJ_DIR); \
		echo "$(PREFIX) $(CYA)$(OBJ_DIR)$(D) $(GRN)$(SUCCESS)$(D)"; \
	else \
		echo "$(PREFIX) $(GRN)no objects$(D)"; \
	fi

fclean: clean
	@echo "$(PREFIX) $(YEL)fclean$(D): removing $(MAG)$(NAME)$(D) and $(CYA)libft$(D)"
	@if [ -f "$(NAME)" ]; then \
		$(RM) $(NAME); \
		echo "$(PREFIX) $(MAG)$(NAME)$(D) $(GRN)$(SUCCESS)$(D)"; \
	else \
		echo "$(PREFIX) $(GRN)no executable$(D)"; \
	fi
	@if [ -d "$(LIBFT_DIR)" ]; then \
		$(RM) $(LIBFT_DIR); \
		echo "$(PREFIX) $(CYA)$(LIBFT_DIR)$(D) $(GRN)$(SUCCESS)$(D)"; \
	else \
		echo "$(PREFIX) $(GRN)no libft folder$(D)"; \
	fi


re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                             Colors Declarations                              #
#                                                                              #
# **************************************************************************** #

# Run the following command to get list of available colors
# bash -c 'for c in {0..255}; do tput setaf $c; tput setaf $c | cat -v; echo =$c; done'
#
B  		= $(shell tput bold)
BLA		= $(shell tput setaf 0)
RED		= $(shell tput setaf 1)
GRN		= $(shell tput setaf 2)
YEL		= $(shell tput setaf 3)
BLU		= $(shell tput setaf 4)
MAG		= $(shell tput setaf 5)
CYA		= $(shell tput setaf 6)
WHI		= $(shell tput setaf 7)
GRE		= $(shell tput setaf 8)
BRED 	= $(shell tput setaf 9)
BGRN	= $(shell tput setaf 10)
BYEL	= $(shell tput setaf 11)
BBLU	= $(shell tput setaf 12)
BMAG	= $(shell tput setaf 13)
BCYA	= $(shell tput setaf 14)
BWHI	= $(shell tput setaf 15)
D 		= $(shell tput sgr0)
BEL 	= $(shell tput bel)
CLR 	= $(shell tput el 1)

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/11 15:11:22 by paalexan          #+#    #+#              #
#    Updated: 2025/09/05 16:10:06 by paalexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                            Variables Declaration                             #
#                                                                              #
# **************************************************************************** #

# Executable
NAME			= cub3D
NAME_BONUS		= cub3D_bonus

# Libft Repository
LIBFT_REPO  	= git@github.com:alteixeira20/42_libft.git
LIBFT_DIR     	= libft
LIBFT         	= $(LIBFT_DIR)/libft.a

# Shell helpers
RM            	= rm -rf

# Message Vars
PREFIX 			= $(B)$(MAG)[cub3D]$(D)
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
SRC_BONUS_DIR 	= src_bonus
INIT_DIR		= $(SRC_DIR)/init
PARSER_DIR		= $(SRC_DIR)/parser
ERROR_DIR		= $(SRC_DIR)/error
CLEANUP_DIR		= $(SRC_DIR)/cleanup
VALIDATION_DIR	= $(SRC_DIR)/validation

MAP_DIR			= maps
OBJ_DIR			= obj
OBJ_BONUS_DIR	= obj_bonus

# **************************************************************************** #
#                                                                              #
#                                 Source Files                                 #
#                                                                              #
# **************************************************************************** #

# Mandatory
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
SRC				+= $(CLEANUP_DIR)/cleanup_util.c
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

# Bonus
SRC_BONUS		= $(SRC_BONUS_DIR)/main.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/init/init.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/init/init_input.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/parser/parser.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/parser/parser_lines.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/parser/parser_color.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/parser/parser_map.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/parser/parser_player.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/parser/parser_player_dir.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/parser/parser_textures.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/parser/parser_utils.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/validation/validation.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/error/error.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/cleanup/cleanup.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/cleanup/cleanup_util.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/draw.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/input.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/input_mouse.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/loop.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/raycast.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/raycast_util.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/render_init.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/render_textures.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/update.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/update_util.c

# **************************************************************************** #
#                                                                              #
#                                   Targets                                    #
#                                                                              #
# **************************************************************************** #

OBJS			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS		= $(SRC_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
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

$(OBJ_BONUS_DIR):
	@mkdir -p $(OBJ_BONUS_DIR)

$(MLX):
	@$(MAKE) $(MLX_DIR) --silent > /dev/null 2>&1
	@echo "$(PREFIX) $(B)MinilibX$(D) compiled $(SUCCESS)."

$(NAME): $(OBJ_DIR) $(MLX) $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) $(LIBFT) $(MLX_LIBS) -o $(NAME)
	@echo "$(PREFIX) $(B)Executable$(D) compiled $(SUCCESS)."

bonus: $(OBJ_BONUS_DIR) $(LIBFT) $(MLX) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(DFLAGS) $(OBJS_BONUS) $(LIBFT) $(MLX_LIBS) -o $(NAME_BONUS)
	@echo "$(PREFIX) $(B)Bonus Executable$(D) compiled $(SUCCESS)."

maps:
	@bash -c '\
		echo "$(PREFIX) $(CYA)Choose map type:$(D)"; \
		echo "1) Invalid"; \
		echo "2) Valid"; \
		read -p "Enter choice: " choice; \
		if [ "$$choice" = "1" ]; then dir="$(MAP_DIR)/invalid"; \
		elif [ "$$choice" = "2" ]; then dir="$(MAP_DIR)/valid"; \
		else echo "Invalid option"; exit 1; fi; \
		MAPS=($$(find $$dir -name "*.cub")); \
		select map in "$${MAPS[@]}"; do \
			[ -z "$$map" ] && echo "Invalid choice" && break; \
			cp "$$map" "./$$(basename $$map)"; \
			./$(NAME) "$$(basename $$map)"; \
			rm "$$(basename $$map)"; \
			break; \
		done'

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME) $(ARGS)

valgrind_invalid:
	@echo "$(PREFIX) $(YEL)Running strict Valgrind checks on invalid maps...$(D)"
	@for bin in $(NAME) $(NAME_BONUS); do \
		if [ -x "$$bin" ]; then \
			echo "$(PREFIX) Testing with executable: $(MAG)$$bin$(D)"; \
			for map in $(MAP_DIR)/invalid/*.cub; do \
				if [ -f "$$map" ]; then \
					valgrind --leak-check=full \
						--show-leak-kinds=all \
						--errors-for-leak-kinds=all \
						--track-origins=yes \
						--error-exitcode=42 \
						./$$bin "$$map" > /dev/null 2>&1; \
					VALGRIND_EXIT=$$?; \
					if [ $$VALGRIND_EXIT -eq 42 ]; then \
						echo "$(PREFIX) $$map $(RED)FAILED$(D) memory check"; \
					else \
						echo "$(PREFIX) $$map $(GRN)PASSED$(D)"; \
					fi; \
				fi; \
			done; \
			echo ""; \
		fi; \
	done


clean:
	@echo "$(PREFIX) $(YEL)clean$(D): removing $(CYA)object files$(D)"
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(RM) $(OBJ_DIR); \
		echo "$(PREFIX) $(CYA)$(OBJ_DIR)$(D) $(GRN)$(SUCCESS)$(D)"; \
	fi
	@if [ -d "$(OBJ_BONUS_DIR)" ]; then \
		$(RM) $(OBJ_BONUS_DIR); \
		echo "$(PREFIX) $(CYA)$(OBJ_BONUS_DIR)$(D) $(GRN)$(SUCCESS)$(D)"; \
	fi

fclean: clean
	@echo "$(PREFIX) $(YEL)fclean$(D): removing executables and $(CYA)libft$(D)"
	@if [ -f "$(NAME)" ]; then \
		$(RM) $(NAME); \
		echo "$(PREFIX) $(MAG)$(NAME)$(D) $(GRN)$(SUCCESS)$(D)"; \
	fi
	@if [ -f "$(NAME_BONUS)" ]; then \
		$(RM) $(NAME_BONUS); \
		echo "$(PREFIX) $(MAG)$(NAME_BONUS)$(D) $(GRN)$(SUCCESS)$(D)"; \
	fi
	@if [ -d "$(LIBFT_DIR)" ]; then \
		$(RM) $(LIBFT_DIR); \
		echo "$(PREFIX) $(CYA)$(LIBFT_DIR)$(D) $(GRN)$(SUCCESS)$(D)"; \
	fi
re: fclean all

.PHONY: all clean fclean re bonus maps valgrind valgrind_invalid

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

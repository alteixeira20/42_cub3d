# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/11 15:11:22 by paalexan          #+#    #+#              #
#    Updated: 2025/10/13 13:59:35 by jopedro-         ###   ########.fr        #
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
MLX_DIR   	= ./mlx

MLX       	= $(MLX_DIR)/libmlx.a
MLX_LIBS  	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

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

# Test helpers
GAME			?= $(NAME_BONUS)
INVALID_MAPS	:= $(shell find $(MAP_DIR)/invalid -type f -name '*.cub' 2>/dev/null)
TEXTURE_TEST_MAP := $(firstword $(wildcard $(MAP_DIR)/valid/*.cub))
HAS_TEXTURE_MAP := $(if $(TEXTURE_TEST_MAP),1,0)
TEXTURES		:= $(shell find assets -type f -name '*.xpm' 2>/dev/null)

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
SRC_BONUS		+= $(SRC_BONUS_DIR)/init/init_utils.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/init/input.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/init/minimap.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/init/render.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/parser/parser.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/parser/lines.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/parser/color.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/parser/map.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/parser/player.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/parser/player_dir.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/parser/textures.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/parser/utils.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/parser/parse_doors.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/validation/validation.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/error/error.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/cleanup/cleanup.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/cleanup/util.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/cleanup/doors_clean.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/render/draw.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/render/draw_utils.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/render/draw_bg.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/render/init.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/render/textures.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/render/textures_utils.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/raycast/raycast.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/raycast/util.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/input/keyboard.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/input/mouse.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/ui/crosshair.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/ui/minimap/minimap.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/ui/minimap/minimap_utils.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/ui/minimap/minimap_sampling.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/ui/minimap/minimap_colors.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/game/loop.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/game/game_screen.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/update/update.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/update/doors_query.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/update/doors_update.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/update/doors_update_util.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/update/util.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/collectibles/keys_load.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/collectibles/draw_utils.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/collectibles/update.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/collectibles/draw.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/ui/hud/hud.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/ui/hud/hud_text.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/ui/hud/hud_utils.c
SRC_BONUS		+= $(SRC_BONUS_DIR)/parser/collectibles.c

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

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS_DIR) $(LIBFT) $(MLX) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(DFLAGS) $(OBJS_BONUS) $(LIBFT) $(MLX_LIBS) -o $(NAME_BONUS)
	@echo "$(PREFIX) $(B)Bonus Executable$(D) compiled $(SUCCESS)."

maps:
	@bash -c '\
		if [ -x "$(NAME_BONUS)" ]; then \
			echo "$(PREFIX) $(CYA)Choose executable:$(D)"; \
			echo "1) Mandatory ($(NAME))"; \
			echo "2) Bonus     ($(NAME_BONUS))"; \
			read -p "Enter choice: " exe_choice; \
			if [ "$$exe_choice" = "1" ]; then \
				BIN="$(NAME)"; \
			elif [ "$$exe_choice" = "2" ]; then \
				BIN="$(NAME_BONUS)"; \
			else \
				echo "$(RED)Invalid executable choice$(D)"; exit 1; \
			fi; \
		else \
			BIN="$(NAME)"; \
		fi; \
		echo ""; \
		echo "$(PREFIX) $(CYA)Choose map type:$(D)"; \
		echo "1) Invalid"; \
		echo "2) Valid"; \
		read -p "Enter choice: " choice; \
		if [ "$$choice" = "1" ]; then dir="$(MAP_DIR)/invalid"; \
		elif [ "$$choice" = "2" ]; then dir="$(MAP_DIR)/valid"; \
		else echo "$(RED)Invalid map type$(D)"; exit 1; fi; \
		echo ""; \
		MAPS=($$(find $$dir -name "*.cub" | sort)); \
		if [ "$${#MAPS[@]}" -eq 0 ]; then \
			echo "$(RED)No maps found in $$dir$(D)"; exit 1; \
		fi; \
		select map in "$${MAPS[@]}"; do \
			[ -z "$$map" ] && echo "$(RED)Invalid choice$(D)" && break; \
			cp "$$map" "./$$(basename $$map)"; \
			echo "$(PREFIX) Running $$BIN with map $$(basename $$map)"; \
			./$$BIN "$$(basename $$map)"; \
			rm "$$(basename $$map)"; \
			break; \
		done'

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME) $(ARGS)

valgrind_bonus: $(NAME_BONUS)
	$(VALGRIND) ./$(NAME_BONUS) $(ARGS)

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

test_invalid:
	@bash -c ' \
		if [ ! -f "$(GAME)" ]; then \
			echo "$(YELLOW)$(PREFIX)$(RESET) No executable found. Please compile the project first (make bonus)."; \
			exit 0; \
		fi; \
		if [ -z "$(INVALID_MAPS)" ]; then \
			echo "$(YELLOW)$(PREFIX)$(RESET) No invalid maps found in maps/invalid."; \
			exit 0; \
		fi; \
		status=0; passed=0; failed=0; skipped=0; \
		echo "$(ORANGE)$(PREFIX)$(RESET) Running Tests on Invalid Maps..."; \
		for map in $(INVALID_MAPS); do \
			echo ; \
			printf "Testing map %s:\\n" "$(YELLOW)$$(basename "$$map")$(RESET)"; \
			msg_output=$$(./$(GAME) "$$map" 2>&1 || true); \
			first=$$(printf "%s" "$$msg_output" | sed -n '1p'); \
			error_line=$$(printf "%s" "$$msg_output" | sed -n "2p"); \
			err_ok=1; \
			if [ "$$first" = "Error" ] && [ -n "$$error_line" ]; then \
				printf "  Error Msg: %s%s%s %s\\n" "$(GREY)" "$$error_line" "$(RESET)" "$(GREEN)OK$(RESET)"; \
			else \
				printf "  Error Msg: %s%s%s %s\\n" "$(GREY)" "$$error_line" "$(RESET)" "$(RED)KO$(RESET)"; \
				printf "%s\\n" "$$msg_output"; \
				err_ok=0; \
			fi; \
			tmp=$$(mktemp); \
			valgrind --leak-check=full --error-exitcode=42 --log-file=$$tmp ./$(GAME) "$$map" > /dev/null 2>&1 || true; \
			vg_output=$$(cat $$tmp); rm -f $$tmp; \
			vg_ok=1; \
			if printf "%s\\n" "$$vg_output" | grep -q "ERROR SUMMARY: 0"; then \
				printf "  Valgrind: %sOK%s\\n" "$(GREEN)" "$(RESET)"; \
			else \
				printf "  Valgrind: %sKO%s\\n" "$(RED)" "$(RESET)"; \
				printf "%s\\n" "$$vg_output"; \
				vg_ok=0; \
			fi; \
			if [ "$$err_ok" -eq 1 ] && [ "$$vg_ok" -eq 1 ]; then \
				passed=$$((passed + 1)); \
			else \
				failed=$$((failed + 1)); \
				status=1; \
			fi; \
		done; \
		if [ "$$failed" -eq 0 ]; then \
			echo "$(ORANGE)$(PREFIX)$(RESET) Congratulations you passed all $(GREEN)$$passed$(RESET) tests."; \
		else \
			echo "$(ORANGE)$(PREFIX)$(RESET) Passed $(GREEN)$$passed$(RESET) tests and $(RED)$$failed$(RESET) tests."; \
		fi; \
		exit $$status'

test_textures:
	@bash -c ' \
		mand_exec="$(NAME)"; \
		bonus_exec="$(NAME_BONUS)"; \
		ceil_map="$(MAP_DIR)/valid/ceiling_blue_floor_grey.cub"; \
		bonus_map="$(MAP_DIR)/valid/map2.cub"; \
		bonus_door_map="$(MAP_DIR)/valid/map_bonus_test.cub"; \
		mode="bonus"; \
		if [ -f "$$bonus_exec" ]; then \
			printf "Run texture tests for mandatory or bonus build? [m/b] (default b): "; \
			read -r choice; \
			if [ "$$choice" = "m" ] || [ "$$choice" = "M" ]; then \
				mode="mandatory"; \
			fi; \
		fi; \
		if [ "$$mode" = "mandatory" ]; then \
			if [ ! -f "$$mand_exec" ]; then \
				echo "$(YELLOW)$(PREFIX)$(RESET) Mandatory executable not found. Building bonus instead."; \
				mode="bonus"; \
			fi; \
		fi; \
		if [ "$$mode" = "mandatory" ]; then \
			game_exec="$$mand_exec"; \
			default_map="$$ceil_map"; \
		else \
			if [ ! -f "$$bonus_exec" ]; then \
				echo "$(YELLOW)$(PREFIX)$(RESET) Bonus executable not found. Please build it first."; \
				exit 0; \
			fi; \
			game_exec="$$bonus_exec"; \
			default_map="$$bonus_map"; \
		fi; \
		if [ ! -f "$$game_exec" ]; then \
			echo "$(YELLOW)$(PREFIX)$(RESET) Selected executable not found (did you build it?)."; \
			exit 1; \
		fi; \
		if [ ! -f "$$default_map" ]; then \
			echo "$(YELLOW)$(PREFIX)$(RESET) Missing test map $$default_map."; \
			exit 1; \
		fi; \
		key_map=$$(find $(MAP_DIR)/valid -maxdepth 1 -type f -name '*keys*.cub' | head -n 1); \
		asset_textures="$(TEXTURES)"; \
		if [ -z "$$asset_textures" ]; then \
			echo "$(YELLOW)$(PREFIX)$(RESET) No textures detected for testing."; \
			exit 0; \
		fi; \
		skip_mand="door_color.xpm fake_wall.xpm wall.xpm door.xpm"; \
		status=0; passed=0; failed=0; skipped=0; \
		for texture in $$asset_textures; do \
			if [ ! -f "$$texture" ]; then \
				continue; \
			fi; \
			bname=$$(basename "$$texture"); \
			skip_texture=0; \
			if [ "$$mode" = "mandatory" ]; then \
				for skip in $$skip_mand; do \
					if [ "$$bname" = "$$skip" ]; then \
						skip_texture=1; \
						break; \
					fi; \
				done; \
			fi; \
			if [ $$skip_texture -eq 1 ]; then \
				echo ; \
				printf "Skipping texture %s%s%s (not used in mandatory build).\\n" "$(YELLOW)" "$$texture" "$(RESET)"; \
				skipped=$$((skipped + 1)); \
				continue; \
			fi; \
			map_to_use="$$default_map"; \
			if [ "$$bname" = "wall_north.xpm" ] || [ "$$bname" = "wall_south.xpm" ] || [ "$$bname" = "wall_east.xpm" ] || [ "$$bname" = "wall_west.xpm" ]; then \
				map_to_use="$$ceil_map"; \
			fi; \
			if [ "$$bname" = "wall.xpm" ] || [ "$$bname" = "door.xpm" ] || [ "$$bname" = "fake_wall.xpm" ]; then \
				map_to_use="$$bonus_map"; \
			fi; \
			if [ "$$bname" = "door_color.xpm" ]; then \
				map_to_use="$$bonus_door_map"; \
			fi; \
			if printf "%s" "$$texture" | grep -q "/key/"; then \
				if [ -n "$$key_map" ]; then \
					map_to_use="$$key_map"; \
				else \
					map_to_use=""; \
				fi; \
			fi; \
			if [ -z "$$map_to_use" ]; then \
				echo ; \
				printf "Skipping texture %s%s%s (no suitable map found).\\n" "$(YELLOW)" "$$texture" "$(RESET)"; \
				skipped=$$((skipped + 1)); \
				continue; \
			fi; \
			dirname=$$(dirname "$$texture"); \
			echo ; \
			printf "Testing texture %s (dir %s):\\n" "$(YELLOW)$$bname$(RESET)" "$$dirname"; \
			save_perms=$$(stat -c %a "$$texture"); \
			chmod 000 "$$texture"; \
			msg_output=$$(./"$$game_exec" "$$map_to_use" 2>&1 || true); \
			chmod $$save_perms "$$texture"; \
			first=$$(printf "%s" "$$msg_output" | sed -n "1p"); \
			error_line=$$(printf "%s" "$$msg_output" | sed -n "2p"); \
			if [ "$$first" = "Error" ] && printf "%s\\n" "$$error_line" | grep -qi "texture path not readable"; then \
				printf "  Error Msg: %s%s%s %s\\n" "$(GREY)" "$$error_line" "$(RESET)" "$(GREEN)OK$(RESET)"; \
				passed=$$((passed + 1)); \
			elif [ "$$first" = "Error" ]; then \
				printf "  Error Msg: %s%s%s %s\\n" "$(GREY)" "$$error_line" "$(RESET)" "$(RED)KO$(RESET)"; \
				printf "%s\\n" "$$msg_output"; \
				failed=$$((failed + 1)); \
				status=1; \
			else \
				printf "  Status: %sSKIPPED%s (texture not loaded by map)\\n" "$(YELLOW)" "$(RESET)"; \
				skipped=$$((skipped + 1)); \
			fi; \
		done; \
		if [ "$$failed" -eq 0 ]; then \
			echo "$(ORANGE)$(PREFIX)$(RESET) Texture tests: $(GREEN)$$passed$(RESET) passed, $(YELLOW)$$skipped$(RESET) skipped."; \
		else \
			echo "$(ORANGE)$(PREFIX)$(RESET) Texture tests: $(GREEN)$$passed$(RESET) passed, $(RED)$$failed$(RESET) failed, $(YELLOW)$$skipped$(RESET) skipped."; \
		fi; \
		exit $$status'

tester: test_invalid test_textures

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

.PHONY: all clean fclean re bonus maps valgrind valgrind_invalid test_invalid test_textures tester

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

# Aliases used by external test helpers
YELLOW	= $(YEL)
GREEN	= $(GRN)
ORANGE	= $(BYEL)
RESET	= $(D)
GREY	= $(GRE)

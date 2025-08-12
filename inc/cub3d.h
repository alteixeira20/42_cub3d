/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:38:43 by paalexan          #+#    #+#             */
/*   Updated: 2025/08/12 01:51:11 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                                                                            */
/*                                 Libraries                                  */
/*                                                                            */
/* ************************************************************************** */

// Standard
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>

// Custom
# include "../../libft/libft/libft.h"

/* ************************************************************************** */
/*                                                                            */
/*                                   Macros                                   */
/*                                                                            */
/* ************************************************************************** */

// Allowed Map Characters
# define MAP_CHARS		" 01NSEW"

// Identifier Tokens
# define ID_NO			"NO"
# define ID_SO			"SO"
# define ID_WE			"WE"
# define ID_EA			"EA"
# define ID_F			"F"
# define ID_C			"C"

// Max Allowed Width
# define MAX_MAP_WIDTH	8192
# define MAX_MAP_HEIGHT	8192
# define MAX_LINE_LEN	16384

// Error Messages
# define ERR_USAGE					"usage: ./cub3d <file.cub>"
# define ERR_CANNOT_OPEN			"cannot open file"
# define ERR_INVALID_ID				"invalid identifier"
# define ERR_INVALID_EXT			"invalid file extension (expected .cub)"
# define ERR_DUP_ID_NO			    "duplicate identifier NO"
# define ERR_DUP_ID_SO				"duplicate identifier SO"
# define ERR_DUP_ID_WE				"duplicate identifier WE"
# define ERR_DUP_ID_EA				"duplicate identifier EA"
# define ERR_DUP_ID_F				"duplicate identifier F"
# define ERR_DUP_ID_C				"duplicate identifier C"
# define ERR_MISSING_ID				"missing identifier"
# define ERR_BAD_COLOR				"invalid color value"
# define ERR_BAD_TEX_PATH			"texture path not readable"
# define ERR_MAP_CHAR				"map contains forbidden character"
# define ERR_MAP_EMPTY_LINE			"empty line inside map"
# define ERR_MAP_AFTER_CONTENT		"content after map block"
# define ERR_MAP_OPEN				"map not closed"
# define ERR_PLAYER_MULTI			"multiple player positions"
# define ERR_PLAYER_MISSING			"missing player"
# define ERR_ALLOC					"allocation failed"

/* ************************************************************************** */
/*                                                                            */
/*                                  Structs                                   */
/*                                                                            */
/* ************************************************************************** */

// Color parsed from Floor or Sky
typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		argb;
	bool	is_set;
}	t_color;

// Textures Paths
typedef struct s_texture
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
}	t_texture;

// Player Status
typedef struct s_player
{
	int		tile_x;
	int		tile_y;
	char	dir_char;
	bool	is_set;
}	t_player;

// Map Settings
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_map_buffer:
{
	char	**items;
	int		count;
	int		capacity;
}	t_map_buffer;

// Game Settings
typedef struct s_game
{
	t_texture	texture;
	t_color		floor_color;
	t_color		ceil_color;
	t_map		map;
	t_player	player;
}	t_game;

/* ************************************************************************** */
/*                                                                            */
/*                            General Declarations                            */
/*                                                                            */
/* ************************************************************************** */

// Initialize Game
void	game_init(t_game *game);

// Cleanup Game
void	clean_game(t_game *game);
void	clean_map_buffer(t_map_buffer *buf);

// Parsing Map
int			parse_map(const char *filepath, t_game *game);
char		*dup_row_trimmed(const char *src);
int			map_buffer_alloc(t_map_buffer *buf, int capacity);
int			map_buffer_populate(t_map_buffer *buf, const char *line);
const char	*rgb_consume_component(const char *scan, int *out_value);
int			parse_color_after_id(const char *row_text, t_color *dst);

// Validations
int		has_cub_extension(const char *str);

// Map Settings
int		map_width(const t_map *map);
int		map_height(const t_map *map);
char	map_tile(const t_map *map, int y, int x);

// Player Status
int		player_x(const t_player *player);
int		player_y(const t_player *player);
char	player_dir(const t_player *player);

// Error Handling
void	print_error(const char *msg);

#endif

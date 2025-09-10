/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:38:43 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/09 18:50:27 by jopedro-         ###   ########.fr       */
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
# include <math.h>

// Custom
# include "../libft/libft/libft.h"
# include "../libft/gnl/get_next_line_bonus.h"
# include "../libft/printf/ft_printf_bonus.h"
# include "../minilibx-linux/mlx.h"

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

// Window Resolution
# define SCR_W 1920
# define SCR_H 1080

// KeyMap
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

// Player Radius
# define COLL_R 0.20

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
# define ERR_BAD_TEXT_PATH			"texture path not readable"
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

// Color parsed from Floor or Ceiling
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
	char	*path;
	bool	is_set;
}	t_texture;

typedef struct s_input
{
	int	forward;
	int	backward;
	int	left;
	int	right;
	int	turn_l;
	int	turn_r;
}	t_input;

// Player Status
typedef struct s_player
{
	int		tile_x;
	int		tile_y;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
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

typedef struct s_map_buffer
{
	char	**items;
	int		count;
	int		capacity;
}	t_map_buffer;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img;

/* Runtime texture image (for NO, SO, WE, EA) */
typedef struct s_rttex
{
	t_img	img;
}	t_rttex;

/* Rendering context */
typedef struct s_render
{
	void	*mlx;
	void	*win;
	t_img	frame;
}	t_render;

// Game Settings
typedef struct s_game
{
	t_texture		tex_no;
	t_texture		tex_so;
	t_texture		tex_we;
	t_texture		tex_ea;
	t_color			floor_color;
	t_color			ceil_color;
	t_map			map;
	t_player		player;
	t_map_buffer	tmp;
	t_render		render;
	t_rttex			tex_rt[4];
	t_input			inp;
}	t_game;

// Parser Helper Struct
typedef struct s_parser_ctx
{
	int				fd;
	t_game			*game;
	t_map_buffer	*buf;
}	t_parser_ctx;

typedef enum e_texid
{
	TEX_NO = 0,
	TEX_SO = 1,
	TEX_WE = 2,
	TEX_EA = 3
}	t_texid;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_x;
	double	delta_y;
	double	perp_dist;
	int		line_h;
	int		draw_start;
	int		draw_end;
	int		tex_id;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_ray;

/* ************************************************************************** */
/*                                                                            */
/*                            General Declarations                            */
/*                                                                            */
/* ************************************************************************** */

// Initialize Game
void	game_init(t_game *game);
void	input_init(t_input *inp);

// Parsing
int		parse_all(const char *path, t_game *game);
int		parse_map(char **lines, int count, t_map *map);
int		parse_player(t_game *game);
int		parse_color(const char *line, t_game *game);
int		parse_color_after_id(const char *row_text, t_color *dst);
int		parse_texture(const char *line, t_game *game);
char	*line_dup_trimmed(const char *src);
int		lines_buf_init(t_map_buffer *buf, int capacity);
int		lines_buf_push(t_map_buffer *buf, const char *line);
int		line_is_spaces_only(const char *str);
int		line_is_map_content(const char *str);
int		process_line(const char *line, int *in_map, t_game *game,
			t_map_buffer *buf);
int		skip_spaces(const char *str, int i);
int		ids_complete(t_game *game);
void	set_dir_and_plane(t_game *game, char c);

// Validations
int		has_cub_extension(const char *str);
int		has_xpm_extension(const char *str);
int		validate_map_closed(t_game *game);

// Map Settings
int		map_width(const t_map *map);
int		map_height(const t_map *map);
char	map_tile(const t_map *map, int y, int x);

// Player Status
int		player_x(const t_player *player);
int		player_y(const t_player *player);
char	player_dir(const t_player *player);
void	rotate_left(t_game *g, double odx, double opx, double rs);
void	rotate_right(t_game *g, double odx, double opx, double rs);

// Raycast
void	ray_setup(t_game *cube, t_ray *r, int x);
void	ray_dda(t_game *cube, t_ray *r);
void	ray_compute_lines(t_game *cube, t_ray *r);
int		ray_pick_tex(const t_ray *r);
void	ray_texcoords_setup(t_game *cube, t_ray *r);
void	ray_set_dir(t_game *cube, t_ray *r);

// Error Handling
void	print_error(const char *msg);

// Cleanup Game
void	clean_game(t_game *game);
void	clean_game_setup(t_game *game);
void	clean_texture(t_texture *t);
void	clean_map(t_map *m);
void	clean_map_buffer(t_map_buffer *buf);
void	clean_str_array(char **arr, int count);
void	print_parse(const t_game *game);

int		render_init(t_game *g);
void	render_destroy(t_game *g);

int		textures_load(t_game *cube);
void	textures_destroy(t_game *cube);

void	draw_frame(t_game *cube);

int		game_loop(void *param);
int		key_press(int keycode, t_game *cube);
int		key_release(int keycode, t_game *cube);
int		win_close(t_game *cube);
void	update_player(t_game *cube);

#endif

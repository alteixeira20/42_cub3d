/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:38:43 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/10 17:44:28 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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
# include <sys/time.h>
# include <stddef.h>

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
# define MAP_CHARS		" 01NSEWDC"

// Identifier Tokens
# define ID_NO			"NO"
# define ID_SO			"SO"
# define ID_WE			"WE"
# define ID_EA			"EA"
# define ID_DO			"DO"
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
# define KEY_M 109

// Input
# define MOUSE_SENS		0.00042
# define MOUSE_SENSE		MOUSE_SENS

// Player Radius
# define COLL_R 0.20

// Collectibles
# define KEY_FRAME_COUNT 24
# define KEY_ANIM_FPS    12.0
# define KEY_BOB_AMP_PX  6
# define KEY_PICKUP_DIST 0.5
# define KEY_SCALE       0.5
# define KEY_TEXT_SCALE  10

// Minimap Settings
# define MM_TILE_SIZE       10
# define MM_RADIUS_TILES    12
# define MM_OFFSET_MARGIN   20
# define MM_SCALE           2.0
# define MM_SS_OFFSET       0.042

// Minimap Colors
# define MM_COLOR_WALL   0x00333333
# define MM_COLOR_FLOOR  0x00777777
# define MM_COLOR_VOID   0x00000000
# define MM_COLOR_BORDER 0x00000000
# define MM_COLOR_PLAYER 0x00FF0000

// Error Messages
# define ERR_USAGE					"usage: ./cub3d <file.cub>"
# define ERR_CANNOT_OPEN			"cannot open file"
# define ERR_INVALID_ID				"invalid identifier"
# define ERR_INVALID_EXT			"invalid file extension (expected .cub)"
# define ERR_DUP_ID_NO			    "duplicate identifier NO"
# define ERR_DUP_ID_SO				"duplicate identifier SO"
# define ERR_DUP_ID_WE				"duplicate identifier WE"
# define ERR_DUP_ID_EA				"duplicate identifier EA"
# define ERR_DUP_ID_DO				"duplicate identifier DO"
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

//Doors
# define DOOR_CELL 'D'
# define DOOR_OPEN_SPEED 0.1f
# define DOOR_RADIUS 2.5f
# define DOOR_THICK 0.9f

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
	int		forward;
	int		backward;
	int		left;
	int		right;
	int		mouse_captured;
	int		last_x;
	int		last_y;
	double	mouse_angle;
	double	mouse_dy;
	double	sens;
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
	double	pitch;
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

typedef struct s_minimap
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;

	int		tile_size;
	int		radius_tiles;
	int		offset_x;
	int		offset_y;

	double	scale;
	bool	enabled;
}	t_minimap;

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

//Doors
typedef struct s_door
{
	int		grid_x;
	int		grid_y;
	float	open_t;
	int		opening;
}	t_door;

typedef struct s_doors
{
	t_door	*arr;
	size_t	len;
}	t_doors;

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

// HUD
typedef struct s_hud_ctx
{
	t_img			*img;
	int				x;
	int				y;
	int				scale;
	unsigned int	color;
	const char		*text;
}	t_hud_ctx;

typedef struct s_hud_glyph
{
	char			c;
	unsigned char	rows[7];
}	t_hud_glyph;

typedef struct s_collectible
{
	int		tile_x;
	int		tile_y;
	double	pos_x;
	double	pos_y;
	int		collected;
	double	phase;
}	t_collectible;

typedef struct s_bounds
{
	int	start_x;
	int	end_x;
	int	start_y;
	int	end_y;
}	t_bounds;

typedef struct s_collectibles
{
	t_img				key_frames[KEY_FRAME_COUNT];
	t_collectible		*items;
	int					count;
	int					collected;
	double				anim_t;
}	t_collectibles;

// Game Settings
typedef struct s_game
{
	t_texture		tex_no;
	t_texture		tex_so;
	t_texture		tex_we;
	t_texture		tex_ea;
	t_texture		tex_do;
	t_color			floor_color;
	t_color			ceil_color;
	t_map			map;
	t_player		player;
	t_map_buffer	tmp;
	t_render		render;
	t_rttex			tex_rt[5];
	t_input			inp;
	t_minimap		minimap;
	t_doors			doors;
	bool			paused;
	t_collectibles	collect;
	double			zbuf[SCR_W];
}	t_game;

/* Collectible sprite draw context */
typedef struct s_drawctx
{
	t_game			*cube;
	t_img			*tex;
	unsigned int	trans;
	double			ty;
}	t_drawctx;

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
	TEX_EA = 3,
	TEX_DO = 4
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
	int		hit_type;
	int		tex_y_off;
	int		base_bottom;
}	t_ray;


/* ************************************************************************** */
/*                                                                            */
/*                            General Declarations                            */
/*                                                                            */
/* ************************************************************************** */

// Initialize Game
void			game_init(t_game *cube);
void			input_init(t_input *inp);
void			minimap_init(t_game *cube);
void			render_init(t_game *cube);
int				render_init_win(t_game *cube);

// Parsing
int				parse_all(const char *path, t_game *cube);
int				parse_map(char **lines, int count, t_map *map);
int				parse_player(t_game *cube);
int				parse_color(const char *line, t_game *cube);
int				parse_color_after_id(const char *row_text, t_color *dst);
int				parse_texture(const char *line, t_game *cube);
char			*line_dup_trimmed(const char *src);
int				lines_buf_init(t_map_buffer *buf, int capacity);
int				lines_buf_push(t_map_buffer *buf, const char *line);
int				line_is_spaces_only(const char *str);
int				line_is_map_content(const char *str);
int				process_line(const char *line, int *in_map, t_game *cube,
					t_map_buffer *buf);
int				skip_spaces(const char *str, int i);
int				ids_complete(t_game *cube);
void			set_dir_and_plane(t_game *cube, char c);

// Validations
int				has_cub_extension(const char *str);
int				has_xpm_extension(const char *str);
int				validate_map_closed(t_game *cube);

// Map Settings
int				map_width(const t_map *map);
int				map_height(const t_map *map);
char			map_tile(const t_map *map, int y, int x);

// HUD
void			hud_put_text(t_game *cube, t_hud_ctx *ctx);
char			*hud_make_counter_text(const t_game *cube);

// Player Status
int				player_x(const t_player *player);
int				player_y(const t_player *player);
char			player_dir(const t_player *player);
void			rotate_left(t_game *cube, double odx, double opx, double rs);

// Raycast
void			ray_setup(t_game *cube, t_ray *r, int x);
void			ray_dda(t_game *cube, t_ray *r);
void			ray_compute_lines(t_game *cube, t_ray *r);
int				ray_pick_tex(const t_ray *r);
void			ray_texcoords_setup(t_game *cube, t_ray *r);
void			ray_set_dir(t_game *cube, t_ray *r);

// Input
void			apply_mouse_yaw(t_game *cube);
void			apply_mouse_pitch(t_game *cube);
void			update_mouse_angle(t_game *cube);
void			mouse_capture_set(t_game *cube, int enable);

// UI
void			render_minimap(t_game *cube);
void			render_player_pos(t_game *cube);
void			draw_crosshair(t_game *cube);
void			draw_border(t_minimap *m, int color);
void			put_pixel(t_minimap *m, int x, int y, int color);
void			clear_minimap(t_minimap *m, int color);
void			get_rgb(unsigned int c, unsigned int *r,
					unsigned int *g, unsigned int *b);

unsigned int	tile_color(char t);
unsigned int	rgb(unsigned int r, unsigned int g, unsigned int b);
unsigned int	sample2x2(const t_game *cube, double sx, double sy);

// Textures Utils
unsigned int	get_texel(const t_img *img, int x, int y);
void			put_pixel_img(t_img *img, int x, int y, unsigned int color);

// Collectible Util
void			sprite_transform(t_game *cube, t_collectible *c,
					double *tx, double *ty);
t_bounds		sprite_bounds(int screen_x,
					int sprite_w, int sprite_h, int v_off);
int				clampi(int v, int lo, int hi);

// Error Handling
void			print_error(const char *msg);

// Cleanup Game
void			clean_game(t_game *cube);
void			clean_map_buffer(t_map_buffer *buf);
void			clean_str_array(char **arr, int count);
void			clean_game_setup(t_game *cube);
void			clean_texture(t_texture *t);
void			clean_map(t_map *m);
void			print_parse(const t_game *cube);
void			clean_doors(t_doors *doors);

void			render_destroy(t_game *cube);

int				textures_load(t_game *cube);
void			textures_destroy(t_game *cube);

// Render
void			draw_frame(t_game *cube);
void			img_put_pixel(t_img *img, int x, int y, unsigned int color);

int				game_loop(void *param);
int				key_press(int keycode, t_game *cube);
int				key_release(int keycode, t_game *cube);
int				mouse_move(int x, int y, void *param);
int				win_close(t_game *cube);
void			update_player(t_game *cube);

void			rotate_player(t_game *cube, double angle);

//Doors
void			parse_doors(t_game *cube);
int				door_blocks_cell(const t_doors *doors, int gx, int gy);
float			door_plane_offset(const t_doors *doors, int gx, int gy);
void			doors_free(t_doors *doors);
void			doors_update(t_doors *doors, char **map, t_vec2 p);
void			update_doors_for_frame(t_game *cube);
int				get_door_screen_offset(t_game *c, const t_ray *r);
void			apply_door_sink(t_game *c, t_ray *r);
void			draw_slice(t_game *c, t_ray *r, int x);
int				ray_find_wall_behind_door(t_game *c, t_ray *rb);
int				advance_one_step(t_game *c, t_ray *r);

// Collectibles
int				parse_collectibles(t_game *cube);
int				keys_load(t_game *cube);
void			clean_keys(t_game *cube);
void			collectibles_update(t_game *cube);
void			collectibles_draw(t_game *cube);

// HUD
void			hud_init(t_hud_ctx *ctx, t_img *frame);
void			hud_draw_collected(t_game *cube);
 
#endif

#include "../inc/cub3d.h"

static void	ray_setup(t_game *cube, t_ray *r, int x)
{
	r->camera_x = 2.0 * x / (double)SCR_W - 1.0;
	r->ray_dir_x = cube->player.dir_x + cube->player.plane_x * r->camera_x;
	r->ray_dir_y = cube->player.dir_y + cube->player.plane_y * r->camera_x;
	r->map_x = (int)cube->player.pos_x;
	r->map_y = (int)cube->player.pos_y;
	r->delta_x = (r->ray_dir_x == 0.0) ? 1e30 : fabs(1.0 / r->ray_dir_x);
	r->delta_y = (r->ray_dir_y == 0.0) ? 1e30 : fabs(1.0 / r->ray_dir_y);
	if (r->ray_dir_x < 0.0)
	{
		r->step_x = -1;
		r->side_dist_x = (cube->player.pos_x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - cube->player.pos_x) * r->delta_x;
	}
	if (r->ray_dir_y < 0.0)
	{
		r->step_y = -1;
		r->side_dist_y = (cube->player.pos_y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - cube->player.pos_y) * r->delta_y;
	}
}

static void	ray_dda(t_game *cube, t_ray *r)
{
	int hit;

	hit = 0;
	while (!hit)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x < 0 || r->map_y < 0
			|| r->map_x >= cube->map.width || r->map_y >= cube->map.height)
			break ;
		if (cube->map.grid[r->map_y][r->map_x] == '1')
			hit = 1;
	}
}

static void	ray_compute_lines(t_game *cube, t_ray *r)
{
	if (r->side == 0)
		r->perp_dist = (r->map_x - cube->player.pos_x
				+ (1 - r->step_x) * 0.5) / r->ray_dir_x;
	else
		r->perp_dist = (r->map_y - cube->player.pos_y
				+ (1 - r->step_y) * 0.5) / r->ray_dir_y;
	if (r->perp_dist < 1e-6)
		r->perp_dist = 1e-6;
	r->line_h = (int)(SCR_H / r->perp_dist);
	r->draw_start = -r->line_h / 2 + SCR_H / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_h / 2 + SCR_H / 2;
	if (r->draw_end >= SCR_H)
		r->draw_end = SCR_H - 1;
}

static int	ray_pick_tex(const t_ray *r)
{
	if (r->side == 0)
	{
		if (r->ray_dir_x > 0.0)
			return (TEX_WE);
		else
			return (TEX_EA);
	}
	if (r->ray_dir_y > 0.0)
		return (TEX_NO);
	return (TEX_SO);
}

static t_img	*ray_tex_img(t_game *cube, int id)
{
	return (&cube->tex_rt[id].img);
}

static void	ray_texcoords_setup(t_game *cube, t_ray *r)
{
	t_img	*img;
	int		tex_w;
	int		tex_h;

	img = ray_tex_img(cube, r->tex_id);
	tex_w = img->w;
	tex_h = img->h;
	if (r->side == 0)
		r->wall_x = cube->player.pos_y + r->perp_dist * r->ray_dir_y;
	else
		r->wall_x = cube->player.pos_x + r->perp_dist * r->ray_dir_x;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * (double)tex_w);
	if ((r->side == 0 && r->ray_dir_x > 0.0)
		|| (r->side == 1 && r->ray_dir_y < 0.0))
		r->tex_x = tex_w - r->tex_x - 1;
	r->step = (double)tex_h / (double)r->line_h;
	r->tex_pos = (r->draw_start - SCR_H / 2 + r->line_h / 2) * r->step;
}

static inline unsigned int	get_texel(const t_img *img, int x, int y)
{
	char			*px;
	unsigned int	color;

	px = img->addr + y * img->line_len + x * (img->bpp / 8);
	color = *(unsigned int *)px;
	return (color);
}

static inline void	put_pixel(t_img *img, int x, int y, unsigned int color)
{
	char	*px;

	px = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)px = color;
}

static void	draw_column(t_game *cube, int x, t_ray *r)
{
	int				y;
	t_img			*tex;
	int				tex_y;
	unsigned int	color;

	tex = ray_tex_img(cube, r->tex_id);
	y = 0;
	while (y < r->draw_start)
	{
		put_pixel(&cube->render.frame, x, y, cube->ceil_color.argb);
		y++;
	}
	while (y <= r->draw_end)
	{
		tex_y = (int)r->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->h)
			tex_y = tex->h - 1;
		color = get_texel(tex, r->tex_x, tex_y);
		if (r->side == 1)
			color = ((color & 0xFFFEFEFE) >> 1);
		put_pixel(&cube->render.frame, x, y, color);
		r->tex_pos += r->step;
		y++;
	}
	while (y < SCR_H)
	{
		put_pixel(&cube->render.frame, x, y, cube->floor_color.argb);
		y++;
	}
}

void	draw_frame(t_game *cube)
{
	int		x;
	t_ray	r;

	x = 0;
	while (x < SCR_W)
	{
		ray_setup(cube, &r, x);
		ray_dda(cube, &r);
		r.tex_id = ray_pick_tex(&r);
		ray_compute_lines(cube, &r);
		ray_texcoords_setup(cube, &r);
		draw_column(cube, x, &r);
		x++;
	}
	mlx_put_image_to_window(cube->render.mlx, cube->render.win,
		cube->render.frame.img, 0, 0);
}

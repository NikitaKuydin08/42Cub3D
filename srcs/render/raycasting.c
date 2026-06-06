/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 08:14:56 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/06/06 15:17:31 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	makeup_color(t_data *data, mlx_texture_t *current_tex, int y, int x)
{
	uint8_t		*px;

	px = &current_tex->pixels[(current_tex->width * y + x) * 4];
	data->color = (px[0] << 24) | (px[1] << 16) | (px[2] << 8) | (px[3]);
}

static void	draw_texture(t_ray *ray, t_data *data, t_texrgbinfo *t, int x)
{
	int	y;
	int	tex_height;

	recognise_side_tex(t, ray);
	tex_height = t->tex[t->index]->height;
	t->line.x = (int)(ray->pos_on_wall * t->tex[t->index]->width);
	if ((ray->side == 0 && ray->ray_x > 0)
		|| (ray->side == 1 && ray->ray_y < 0))
		t->line.x = t->tex[t->index]->width - t->line.x - 1;
	t->line.step = 1.0 * tex_height / ray->line_height;
	t->line.pos = (ray->draw_start - data->win_height / 2 + ray->line_height
			/ 2) * t->line.step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		t->line.y = (int)t->line.pos & (tex_height - 1);
		t->line.pos += t->line.step;
		makeup_color(data, t->tex[t->index], t->line.y, t->line.x);
		if (data->color > 0)
			data->texture_pixels[x][y] = data->color;
		y++;
	}
}

static void	distance_ray_to_wall(t_ray *ray, t_player *player, t_data *data)
{
	if (ray->side == 0)
		ray->distwall = ray->sidedist_x - ray->deltadist_x;
	else
		ray->distwall = ray->sidedist_y - ray->deltadist_y;
	if (ray->distwall < 0.0001)
		ray->distwall = 0.0001;
	ray->line_height = (int)(data->win_height / ray->distwall);
	if (ray->line_height < 0)
		ray->line_height = 0;
	ray->draw_start = (data->win_height / 2) - (ray->line_height / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (data->win_height / 2) + (ray->line_height / 2);
	if (ray->draw_end >= data->win_height)
		ray->draw_end = data->win_height - 1;
	if (ray->side == 0)
		ray->pos_on_wall = player->pos_y + ray->distwall * ray->ray_y;
	else
		ray->pos_on_wall = player->pos_x + ray->distwall * ray->ray_x;
	ray->pos_on_wall -= floor(ray->pos_on_wall);
}

static void	do_dda(t_ray *ray, t_data *data)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (!check_limit_dda(data, ray->map_x, ray->map_y))
			break ;
		if (data->map[ray->map_y][ray->map_x] > '0')
			ray->hit = 1;
	}
}

void	raycasting(t_player *player, t_data *data)
{
	t_ray	ray;
	int		x;
	int		y;

	ray = data->ray;
	x = 0;
	while (x < data->win_width)
	{
		y = 0;
		init_raycasting_dda(&ray, x, player);
		do_dda(&ray, data);
		distance_ray_to_wall(&ray, player, data);
		while (y < ray.draw_start)
			data->texture_pixels[x][y++] = data->texrgbinfo.hex_ceiling;
		y = ray.draw_end;
		while (y < data->win_height)
			data->texture_pixels[x][y++] = data->texrgbinfo.hex_floor;
		draw_texture(&ray, data, &data->texrgbinfo, x);
		x++;
	}
}

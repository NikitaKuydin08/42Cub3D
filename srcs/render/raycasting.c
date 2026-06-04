/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-16 08:14:56 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-05-16 08:14:56 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	recognise_side_tex(t_texrgbinfo *texinfo, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_x < 0)
			texinfo->index = WEST;
		else
			texinfo->index = EAST;
	}
	else
	{
		if (ray->ray_y < 0)
			texinfo->index = NORTH;
		else
			texinfo->index = SOUTH;
	}
}

static void	draw_texture(t_ray *ray, t_data *data, t_texrgbinfo *t, int x)
{
	int	y;
	uint32_t	color;
	int			texHeight;

	recognise_side_tex(t, ray);
	texHeight = t->tex[t->index]->height;
	t->line.x = (int)(ray->pos_on_wall * t->tex[t->index]->width);
	if ((ray->side == 0 && ray->ray_x > 0)
		|| (ray->side == 1 && ray->ray_y < 0))
		t->line.x = t->tex[t->index]->width - t->line.x - 1;
	t->line.step = 1.0 * texHeight / ray->lineHeight;
	t->line.pos = (ray->drawStart - data->win_height / 2 + ray->lineHeight
		/ 2) * t->line.step;
	y = ray->drawStart;
	while (y < ray->drawEnd)
	{
		t->line.y = (int)t->line.pos & (texHeight - 1);
		t->line.pos += t->line.step;
		color = (uint32_t)t->tex[t->index]->pixels[texHeight * t->line.y + t->line.x];
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		if (color > 0)
			data->texture_pixels[x][y] = color;
		y++;
	}
}

static void	distance_ray_to_wall(t_ray *ray, t_player *player, t_data *data)
{
	if (ray->side == 0)
		ray->DistWall = ray->sideDistX - ray->deltaDistX;
	else
		ray->DistWall = ray->sideDistY - ray->deltaDistY;
	ray->lineHeight = (int)(data->win_height / ray->DistWall);
	ray->drawStart = (data->win_height / 2) - (ray->lineHeight / 2);
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = (data->win_height / 2) + (ray->lineHeight / 2);
	if (ray->drawEnd >= data->win_height)
		ray->drawEnd = data->win_height - 1;
	if (ray->side == 0)
		ray->pos_on_wall = player->pos_y + ray->DistWall * player->dir_y;
	else
		ray->pos_on_wall = player->pos_x + ray->DistWall * player->dir_x;
	ray->pos_on_wall -= (int)ray->pos_on_wall;
}

static void	do_dda(t_ray *ray, t_data *data)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->map_x += ray->stepX;
			ray->side = 0; // x grid
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->map_y += ray->stepY;
			ray->side = 1; // y grid
		}
		if (!check_limit_dda(data, ray->map_x, ray->map_y))
			break ;
		if (data->map[ray->map_y][ray->map_x] > '0')
			ray->hit = 1;
	}
}

void	raycasting(t_player *player, t_data *data)
{
    t_ray   ray;
    int	x;
	int	y;

    ray = data->ray;
	x = 0;
	while (x < data->win_width)
	{
		y = 0;
		init_raycasting_dda(&ray, x, player);
		do_dda(&ray, data);
		distance_ray_to_wall(&ray, player, data);
		while (y < ray.drawStart)
			data->texture_pixels[x][y++] = data->texrgbinfo.hex_ceiling;
		y = ray.drawEnd;
		while (y < data->win_height)
			data->texture_pixels[x][y++] = data->texrgbinfo.hex_floor;
		draw_texture(&ray, data, &data->texrgbinfo, x);
		x++;
	}
}


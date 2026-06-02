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

// static void	draw_texture(t_ray *ray, t_data *data, t_texrgbinfo *tex, int x)
// {

// }

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
			ray->sideDistY = ray->deltaDistY;
			ray->map_y += ray->stepY;
			ray->side = 1; // y grid
		}
		if (data->map[ray->map_x][ray->map_y] > '0')
			ray->hit = 1;
	}
}

void	raycasting(t_player *player, t_data *data)
{
    t_ray   ray;
    int	x;

    ray = data->ray;
	x = 0;
	while (x < data->win_width)
	{
		init_raycasting_dda(&ray, x, player);
		do_dda(&ray, data);
		distance_ray_to_wall(&ray, player, data);
		// draw_texture(&ray, data, &data->texrgbinfo, x);
		x++;
	}
}


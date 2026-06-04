/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-15 04:06:50 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-05-15 04:06:50 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	prep_direction_ns(t_player *player)
{
	if (player->orientation == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.60;
		player->plane_y = 0;
	}
	else if (player->orientation == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.60;
		player->plane_y = 0;
	}
}

static void	prep_direction_we(t_player *player)
{
	if (player->orientation == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.60;
	}
	else if (player->orientation == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.60;
	}
}

void	prep_game(t_data *data)
{
	t_player	*player;
	int			i;

	i = -1;
	player = &data->player;
	player->pos_x = (double)player->x + 0.5;
	player->pos_y = (double)player->y + 0.5;
	prep_direction_ns(player);
	prep_direction_we(player);
	data->texrgbinfo.tex[NORTH] = mlx_load_png(data->texrgbinfo.north);
	data->texrgbinfo.tex[SOUTH] = mlx_load_png(data->texrgbinfo.south);
	data->texrgbinfo.tex[WEST] = mlx_load_png(data->texrgbinfo.west);
	data->texrgbinfo.tex[EAST] = mlx_load_png(data->texrgbinfo.east);
	data->texture_pixels = ft_calloc(data->win_width, sizeof(uint32_t*));
	while (++i < data->win_width)
		data->texture_pixels[i] = ft_calloc(data->win_height, sizeof(uint32_t));
}

void	setup_jump_algo(t_ray *ray, t_player *player)
{
	if (ray->ray_x > 0)
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->map_x + 1.0 - player->pos_x) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = -1;
		ray->sideDistX = (player->pos_x - ray->map_x) * ray->deltaDistX;
	}
	if (ray->ray_y > 0)
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->map_y + 1.0 - player->pos_y) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = -1;
		ray->sideDistY = (player->pos_y - ray->map_y) * ray->deltaDistY;
	}
}

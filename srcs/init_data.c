/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-04-24 10:04:16 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-04-24 10:04:16 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_textures(t_texrgbinfo *texinfo)
{
	int	i;

	i = -1;
	texinfo->north = NULL;
	texinfo->south = NULL;
	texinfo->east = NULL;
	texinfo->west = NULL;
	texinfo->floor = NULL;
	texinfo->ceiling = NULL;
	texinfo->hex_ceiling = 0;
	texinfo->hex_floor = 0;
	while (++i < 4)
		texinfo->tex[i] = NULL;
}

void	init_player(t_player *player)
{
	player->orientation = '0';
	player->x = 0;
	player->y = 0;
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
}

void	init_ray(t_ray *ray)
{
	ray->cameraX = 0;
	ray->ray_x = 0.0;
	ray->ray_y = 0.0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->sideDistX = 0.0;
	ray->sideDistY = 0.0;
	ray->deltaDistX = 0.0;
	ray->deltaDistY = 0.0;
	ray->stepX = 0;
	ray->stepY = 0;
	ray->hit = 0;
	ray->DistWall = 0.0;
	ray->drawEnd = 0;
	ray->drawStart = 0;
	ray->lineHeight = 0;
	ray->pos_on_wall = 0.0;
}

void	init_raycasting_dda(t_ray *ray, int x, t_player *player)
{
	init_ray(ray);
	ray->cameraX = (2 * x) / (double)WIN_WIDTH - 1;
	ray->ray_x = player->dir_x + player->plane_x * ray->cameraX;
	ray->ray_y = player->dir_y + player->plane_y * ray->cameraX;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->deltaDistX = fabs(1 / ray->ray_x);
	ray->deltaDistY = fabs(1 / ray->ray_y);
	setup_jump_algo(ray, player);
}

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->image = NULL;
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	data->file = NULL;
	data->path = NULL;
	data->fd = 0;
	data->line_count = 0;
	data->map = NULL;
	data->map_idx = 0;
	data->map_line = 0;
	data->map_started = false;
	data->row_count = 0;
	data->needs_redraw = false;
	init_textures(&data->texrgbinfo);
	init_player(&data->player);
	data->texture_pixels = NULL;
}

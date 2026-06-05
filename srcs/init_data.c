/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:04:16 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/06/05 23:16:30 by nkuydin          ###   ########.fr       */
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
	ray->camera_x = 0;
	ray->ray_x = 0.0;
	ray->ray_y = 0.0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->sidedist_x = 0.0;
	ray->sidedist_y = 0.0;
	ray->deltadist_x = 0.0;
	ray->deltadist_y = 0.0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = 0;
	ray->distwall = 0.0;
	ray->draw_end = 0;
	ray->draw_start = 0;
	ray->line_height = 0;
	ray->pos_on_wall = 0.0;
}

void	init_raycasting_dda(t_ray *ray, int x, t_player *player)
{
	init_ray(ray);
	ray->camera_x = (2 * x) / (double)WIN_WIDTH - 1;
	ray->ray_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->deltadist_x = fabs(1 / ray->ray_x);
	ray->deltadist_y = fabs(1 / ray->ray_y);
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
	data->row_lengths = NULL;
	data->row_count = 0;
	data->needs_redraw = false;
	init_textures(&data->texrgbinfo);
	init_player(&data->player);
	data->texture_pixels = NULL;
	data->delete = false;
	data->close = false;
	data->terminate = false;
}

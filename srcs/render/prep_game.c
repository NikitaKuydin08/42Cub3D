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

void	prep_direction(t_player *player)
{
	if (player->orientation == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (player->orientation == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (player->orientation == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	else if (player->orientation == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
}

void	prep_game(t_data *data)
{
	t_player	*player;

	player = &data->player;
	player->pos_x = (double)player->x + 0.5;
	player->pos_y = (double)player->y + 0.5;
	prep_direction(player);
	data->texrgbinfo.tex[NORTH] = mlx_load_png(data->texrgbinfo.north);
	data->texrgbinfo.tex[SOUTH] = mlx_load_png(data->texrgbinfo.south);
	data->texrgbinfo.tex[WEST] = mlx_load_png(data->texrgbinfo.west);
	data->texrgbinfo.tex[EAST] = mlx_load_png(data->texrgbinfo.east);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 07:19:25 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/06/06 15:16:36 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// static void	draw_minimap(t_data *data)
// {
	
// }

static void	draw_image(t_data *data)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < (uint32_t)data->win_height)
	{
		x = 0;
		while (x < (uint32_t)data->win_width)
		{
			mlx_put_pixel(data->image, x, y, data->texture_pixels[x][y]);
			x++;
		}
		y++;
	}
}

void	draw_game(t_data *data, t_player *player)
{
	raycasting(player, data);
	draw_image(data);
	// if (BONUS)
	// 	draw_minimap(data);
}

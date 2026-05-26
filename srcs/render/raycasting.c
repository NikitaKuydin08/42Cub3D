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

void	raycasting(t_player *player, t_data *data)
{
    t_ray   ray;
    int	x;

    ray = data->ray;
	x = 0;
	while (x < data->win_width)
	{
		init_raycasting_dda(&ray, x, player);
	}
}


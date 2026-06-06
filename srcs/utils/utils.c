/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:53:32 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/06/05 17:07:28 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_limit_dda(t_data *data, int x, int y)
{
	if (y < 0 || y >= data->row_count)
		return (0);
	if (x < 0 || x >= data->row_lengths[y])
		return (0);
	return (1);
}

void	recognise_side_tex(t_texrgbinfo *texinfo, t_ray *ray)
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

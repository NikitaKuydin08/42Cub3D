/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_n_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:41:55 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/06/05 20:58:24 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// 	MLX_KEY_W				= 87,
//  MLX_KEY_A				= 65,
// 	MLX_KEY_D				= 68,
// 	MLX_KEY_S				= 83,
// 	MLX_KEY_ESCAPE			= 256,
// 	MLX_KEY_LEFT			= 263,
// 	MLX_KEY_RIGHT			= 262,
//	MLX_KEY_DOWN			= 264,
//	MLX_KEY_UP				= 265,

static void	validate_move(t_data *data, double new_x, double new_y)
{
	if (check_limit_dda(data, new_x, data->player.pos_y)
		&& data->map[(int)data->player.pos_y][(int)new_x] == '0')
		data->player.pos_x = new_x;
	if (check_limit_dda(data, data->player.pos_x, new_y)
		&& data->map[(int)new_y][(int)data->player.pos_x] == '0')
		data->player.pos_y = new_y;
}

static void	ft_move(t_data *data, int key)
{
	double	new_x;
	double	new_y;

	if (key == FORWARD)
	{
		new_x = data->player.pos_x + data->player.dir_x * MOVE_SPEED;
		new_y = data->player.pos_y + data->player.dir_y * MOVE_SPEED;
	}
	else if (key == BACKWARD)
	{
		new_x = data->player.pos_x - data->player.dir_x * MOVE_SPEED;
		new_y = data->player.pos_y - data->player.dir_y * MOVE_SPEED;
	}
	else if (key == LEFT)
	{
		new_x = data->player.pos_x - data->player.plane_x * MOVE_SPEED;
		new_y = data->player.pos_y - data->player.plane_y * MOVE_SPEED;
	}
	else
	{
		new_x = data->player.pos_x + data->player.plane_x * MOVE_SPEED;
		new_y = data->player.pos_y + data->player.plane_y * MOVE_SPEED;
	}
	validate_move(data, new_x, new_y);
}

static void	ft_rotate(t_data *data, double rot_key)
{
	double	olddir_x;
	double	oldplane_x;
	double	rot_speed;

	if (rot_key == ROT_LEFT)
		rot_speed = ROT_LEFT;
	else
		rot_speed = ROT_RIGHT;
	olddir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(rot_speed)
		- data->player.dir_y * sin(rot_speed);
	data->player.dir_y = olddir_x * sin(rot_speed)
		+ data->player.dir_y * cos(rot_speed);
	oldplane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(rot_speed)
		- data->player.plane_y * sin(rot_speed);
	data->player.plane_y = oldplane_x * sin(rot_speed)
		+ data->player.plane_y * cos(rot_speed);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == 256 && keydata.action == 1)
	{
		if (data && data->mlx)
			mlx_close_window(data->mlx);
		return ;
	}
	else if (keydata.key == 87 || keydata.key == 265)
		ft_move(data, FORWARD);
	else if (keydata.key == 83 || keydata.key == 264)
		ft_move(data, BACKWARD);
	else if (keydata.key == 65)
		ft_move(data, LEFT);
	else if (keydata.key == 68)
		ft_move(data, RIGHT);
	else if (keydata.key == MLX_KEY_LEFT)
		ft_rotate(data, ROT_LEFT);
	else if (keydata.key == MLX_KEY_RIGHT)
		ft_rotate(data, ROT_RIGHT);
	data->needs_redraw = true;
}

void	loop_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->needs_redraw)
	{
		draw_game(data, &data->player);
		data->needs_redraw = false;
	}
}

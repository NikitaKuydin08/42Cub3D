/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 09:48:17 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/06/05 23:16:54 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// EVERYWHERE the function returns 1 on failure

static int	init_row_lengths(t_data *data)
{
	int	i;
	int	len;

	i = 0;
	data->row_lengths = ft_calloc(data->row_count, sizeof(int));
	if (!data->row_lengths)
		return (1);
	while (i < data->row_count)
	{
		if (!data->map[i])
			return (1);
		len = ft_strlen(data->map[i]);
		if (len > 0 && (data->map[i][len - 1] == '\n'))
			len--;
		while (len > 0 && (data->map[i][len - 1] == ' '))
			len--;
		data->row_lengths[i] = len;
		i++;
	}
	return (0);
}

void	start_game(t_data *data)
{
	prep_game(data);
	data->mlx = mlx_init(data->win_width, data->win_height, "cub3d", false);
	if (!data->mlx)
		ft_error(data, 1, NOT_INIT);
	data->image = mlx_new_image(data->mlx, data->win_width,
			data->win_height);
	if (!data->image)
		ft_error(data, 1, NOT_INIT_IMG_BUF);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) < 0)
		ft_error(data, 1, CANT_CREATE_INSTANCE);
	draw_game(data, &data->player);
	mlx_key_hook(data->mlx, key_hook, data);
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_loop(data->mlx);
	free_data(data);
}

int	parsing(t_data *data, char **argv)
{
	if (check_file(argv[1], true))
		ft_error(data, 0, NULL);
	if (map_copy_into_file(argv[1], data))
		ft_error(data, 0, NULL);
	if (extract_data_from_file(data))
		return (free_data(data));
	if (check_textures(&data->texrgbinfo))
		return (free_data(data));
	if (check_map(data))
		return (free_data(data));
	if (init_row_lengths(data))
		return (free_data(data));
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (print_err_msg(USAGE));
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (1);
	init_data(data);
	if (parsing(data, argv) != 0)
		return (0);
	// header();
	start_game(data);
	return (0);
}

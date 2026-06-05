/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:34:37 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/06/05 23:34:22 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_tab(void **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

void	free_map(t_data *data)
{
	if (data->map)
		free_tab((void **)data->map);
	if (data->file)
		free_tab((void **)data->file);
	if (data->fd > 0)
		close(data->fd);
	if (data->path)
		free(data->path);
	if (data->row_lengths)
		free(data->row_lengths);
}

void	free_texinfo(t_texrgbinfo *textures)
{
	int	i;

	i = -1;
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
	if (textures->ceiling)
		free(textures->ceiling);
	if (textures->floor)
		free(textures->floor);
	while (textures->tex[++i])
		mlx_delete_texture(textures->tex[i]);
}

void	free_texture_pixels(t_data *data)
{
	int	i;

	i = 0;
	if (!data->texture_pixels)
		return ;
	while (i < data->win_width)
	{
		free(data->texture_pixels[i]);
		i++;
	}
	free(data->texture_pixels);
	data->texture_pixels = NULL;
}

int	free_data(t_data *data)
{
	if (!data)
		return (1);
	if (data->image && data->mlx && !data->delete)
	{
		mlx_delete_image(data->mlx, data->image);
		data->image = NULL;
		data->delete = true;
	}
	// if (data->mlx && !data->close)
	// {
	// 	mlx_close_window(data->mlx);
	// 	data->close = true;
	// }
	if (data->mlx && !data->terminate)
	{
		mlx_terminate(data->mlx);
		data->mlx = NULL;
		data->terminate = true;
	}
	free_map(data);
	free_texinfo(&data->texrgbinfo);
	free_texture_pixels(data);
	free(data);
	return (1);
}

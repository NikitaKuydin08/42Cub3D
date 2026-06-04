/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-08 10:34:37 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-05-08 10:34:37 by Nikita_Kuydin    ###   ########.fr       */
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
	while(textures->tex[++i])
		free(textures->tex[i]);
}

int	free_data(t_data *data)
{
	free_map(data);
	if (data->texture_pixels)
		free_tab((void **)data->texture_pixels);
	free_texinfo(&data->texrgbinfo);
	free(data);
	return (1);
}

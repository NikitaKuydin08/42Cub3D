/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-08 14:53:32 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-05-08 14:53:32 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int check_limit_dda(t_data *data, int x, int y)
{
    if (y < 0 || y >= data->row_count)
        return (0);
    if (x < 0 || x >= data->row_lengths[y])
        return (0);
    return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 07:12:57 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/06/05 21:10:10 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	print_err_msg(char *msg)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
	return (1);
}

void	ft_error(t_data *data, int exit_code, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	if (!data)
		exit(exit_code);
	free_data(data);
	exit(exit_code);
}

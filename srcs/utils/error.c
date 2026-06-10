/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateon <mateon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 07:12:57 by Nikita_Kuyd       #+#    #+#             */
/*   Updated: 2026/06/10 17:10:24 by mateon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
// the tester works with error message 1 but not with 2 
// (might need to change it to 2 later))

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

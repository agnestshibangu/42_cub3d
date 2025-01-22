/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:12:55 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/13 13:12:56 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	handle_mouse_move(int x, int y, t_data *data)
{
	(void) y;
	if (x > data->mouse_x)
		turn_right(&data->map_data);
	else if (x < data->mouse_x)
		turn_left(&data->map_data);
	mlx_mouse_move(data->mlx, data->mlx_win, SC_WIDTH / 2, SC_HEIGHT / 2);
	return (1);
}

int	close_and_clean(t_data *data)
{
	clean_all(data);
	exit(1);
	return (0);
}

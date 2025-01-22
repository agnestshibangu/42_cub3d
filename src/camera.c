/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:11:43 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/13 13:11:44 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	turn_left(t_map_data *map_data)
{
	rotate(&map_data->player, ROT_SPEED, 1);
	map_data->player.angle = atan2(map_data->player.dir_x,
			map_data->player.dir_y);
}

void	turn_right(t_map_data *map_data)
{
	rotate(&map_data->player, ROT_SPEED, -1);
	map_data->player.angle = atan2(map_data->player.dir_x,
			map_data->player.dir_y);
}

void	rotate(t_player *data, double rotSpeed, int direction)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	old_plane_x = data->plane_x;
	data->dir_x = data->dir_x * cos(rotSpeed * direction)
		- data->dir_y * sin(rotSpeed * direction);
	data->dir_y = old_dir_x * sin(rotSpeed * direction)
		+ data->dir_y * cos(rotSpeed * direction);
	data->plane_x = data->plane_x * cos(rotSpeed * direction)
		- data->plane_y * sin(rotSpeed * direction);
	data->plane_y = old_plane_x * sin(rotSpeed * direction)
		+ data->plane_y * cos(rotSpeed * direction);
	data->angle = atan2(data->dir_x, data->dir_y);
}

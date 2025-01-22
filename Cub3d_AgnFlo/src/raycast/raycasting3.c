/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmuller <flmuller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:39:48 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/13 13:14:18 by flmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_raydir(t_data *data)
{
	double	camera_x;

	camera_x = 2 * data->verl_inf->x / (double)SC_WIDTH - 1;
	data->raydir.x = data->map_data.player.dir_x + data->map_data.player.plane_x
		* camera_x;
	data->raydir.y = data->map_data.player.dir_y + data->map_data.player.plane_y
		* camera_x;
}

void	cast_rays_and_render(t_data *data)
{
	int	side;

	data->verl_inf->x = 0;
	while (data->verl_inf->x < SC_WIDTH)
	{
		init_raydir(data);
		side = raycast(data);
		verline(data, get_textureindex(data, side));
		draw_ceiling(data);
		draw_floor(data);
		data->verl_inf->x++;
	}
}

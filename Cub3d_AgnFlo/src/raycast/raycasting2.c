/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:15:25 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/10 15:30:51 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_define(double perp_wall_d, t_data *data)
{
	int	lineheight;

	lineheight = (int)(SC_HEIGHT / perp_wall_d);
	data->line_height = lineheight;
	data->verl_inf->drawstart = -lineheight / 2 + SC_HEIGHT / 2;
	if (data->verl_inf->drawstart < 0)
		data->verl_inf->drawstart = 0;
	data->verl_inf->drawend = lineheight / 2 + SC_HEIGHT / 2;
	if (data->verl_inf->drawend >= SC_HEIGHT)
		data->verl_inf->drawend = SC_HEIGHT - 1;
}

void	calc_wallx(double *wallx, t_data *data, int side, double perp_wall_d)
{
	if (side == 0)
		*wallx = (data->map_data.player_pos_y + perp_wall_d * data->raydir.y);
	else
		*wallx = (data->map_data.player_pos_x + perp_wall_d * data->raydir.x);
	*wallx -= floor(*wallx);
}

int	get_textureindex(t_data *data, int side)
{
	if (side == 0)
	{
		if (data->raydir.x > 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (data->raydir.y > 0)
			return (2);
		else
			return (3);
	}
}

int	get_texturex(t_data *data, double wallx, int side)
{
	int	texture_width;

	texture_width = data->texture[get_textureindex(data, side)].width;
	data->verl_inf->texturex = (int)(wallx * texture_width);
	if ((side == 0 && data->raydir.x > 0) || (side == 1 && data->raydir.y < 0))
		data->verl_inf->texturex = texture_width - data->verl_inf->texturex - 1;
	return (data->verl_inf->texturex);
}

int	raycast(t_data *data)
{
	double	perp_wall_d;
	int		side;
	t_coord	map;
	double	wallx;

	map.x = (int)data->map_data.player_pos_x;
	map.y = (int)data->map_data.player_pos_y;
	calc_dist(data, &map, &side, &perp_wall_d);
	draw_define(perp_wall_d, data);
	calc_wallx(&wallx, data, side, perp_wall_d);
	data->verl_inf->texturex = get_texturex(data, wallx, side);
	return (side);
}

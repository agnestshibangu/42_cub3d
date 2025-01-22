/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:13:14 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/13 13:13:15 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	valid_pos(t_map_data *map_data, float x, float y)
{
	char	c;

	c = map_data->map[(int)y][(int)x];
	if (c != '0' && c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (0);
	if (fabs(x - floor(x)) < BUFFER_DIST
		&& map_data->map[(int)y][(int)x - 1] == '1')
		return (0);
	if (fabs(x - ceil(x)) < BUFFER_DIST
		&& map_data->map[(int)y][(int)x + 1] == '1')
		return (0);
	if (fabs(y - floor(y)) < BUFFER_DIST
		&& map_data->map[(int)y - 1][(int)x] == '1')
		return (0);
	if (fabs(y - ceil(y)) < BUFFER_DIST
		&& map_data->map[(int)y + 1][(int)x] == '1')
		return (0);
	return (1);
}

void	forward(t_map_data *map_data)
{
	t_pos	player;

	player.x = map_data->player_pos_x;
	player.y = map_data->player_pos_y;
	player.x += map_data->player.dir_x * SPEED;
	player.y += map_data->player.dir_y * SPEED;
	if (valid_pos(map_data, player.y, player.x))
	{
		map_data->player.ppos.x = player.y;
		map_data->player.ppos.y = player.x;
		map_data->player_pos_x = player.x;
		map_data->player_pos_y = player.y;
	}
}

void	backward(t_map_data *map_data)
{
	t_pos	player;

	player.x = map_data->player_pos_x;
	player.y = map_data->player_pos_y;
	player.x -= map_data->player.dir_x * SPEED;
	player.y -= map_data->player.dir_y * SPEED;
	if (valid_pos(map_data, player.y, player.x))
	{
		map_data->player.ppos.x = player.y;
		map_data->player.ppos.y = player.x;
		map_data->player_pos_x = player.x;
		map_data->player_pos_y = player.y;
	}
}

void	strafe_left(t_map_data *map_data)
{
	t_pos	player;

	player.x = map_data->player.ppos.x;
	player.y = map_data->player.ppos.y;
	player.x += cos(map_data->player.angle - M_PI / 2) * SPEED;
	player.y += sin(map_data->player.angle - M_PI / 2) * SPEED;
	if (valid_pos(map_data, player.x, player.y))
	{
		map_data->player.ppos.x = player.x;
		map_data->player.ppos.y = player.y;
		map_data->player_pos_x = player.y;
		map_data->player_pos_y = player.x;
	}
}

void	strafe_right(t_map_data *map_data)
{
	t_pos	player;

	player.x = map_data->player.ppos.x;
	player.y = map_data->player.ppos.y;
	player.x += cos(map_data->player.angle + M_PI / 2) * SPEED;
	player.y += sin(map_data->player.angle + M_PI / 2) * SPEED;
	if (valid_pos(map_data, player.x, player.y))
	{
		map_data->player.ppos.x = player.x;
		map_data->player.ppos.y = player.y;
		map_data->player_pos_x = player.y;
		map_data->player_pos_y = player.x;
	}
}

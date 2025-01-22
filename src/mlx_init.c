/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:13:10 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/13 13:13:11 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_win(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, SC_WIDTH, SC_HEIGHT, GAME_NAME);
}

void	init_map(t_data *data)
{
	char	c;

	data->screen_width = SC_WIDTH;
	data->screen_height = SC_HEIGHT;
	define_player_pos(&data->map_data);
	data->map_data.player.angle = M_PI;
	data->mouse_x = SC_WIDTH / 2;
	data->map_data.player.ppos.x = data->map_data.player_pos_y;
	data->map_data.player.ppos.y = data->map_data.player_pos_x;
	c = data->map_data.map[(int)data->map_data.player.ppos.y]
	[(int)data->map_data.player.ppos.x];
	if (c == 'N')
		data->map_data.player.angle = 3 * data->map_data.player.angle / 2;
	else if (c == 'S')
		data->map_data.player.angle /= 2;
	else if (c == 'E')
		data->map_data.player.angle = 0;
	data->map_data.player.dir_x = sin(data->map_data.player.angle);
	data->map_data.player.dir_y = cos(data->map_data.player.angle);
	calc_plane(&data->map_data.player);
}

void	calc_plane(t_player *player)
{
	double	planescale;

	planescale = tan((FOV * M_PI / 180) / 2);
	player->plane_x = player->dir_y * planescale;
	player->plane_y = -player->dir_x * planescale;
}

void	init_var(t_data *data)
{
	data->keys[0] = 0;
	data->keys[1] = 0;
	data->keys[2] = 0;
	data->keys[XK_w] = 0;
	data->keys[XK_s] = 0;
	data->keys[XK_a] = 0;
	data->keys[XK_d] = 0;
	data->img = 0;
}

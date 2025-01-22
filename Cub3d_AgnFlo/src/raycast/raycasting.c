/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:48:12 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/08 15:59:07 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	calc_deltadist(t_data *data, t_dpos *deltadist)
{
	if (data->raydir.x == 0)
		deltadist->x = 1e30;
	else
		deltadist->x = fabs(1 / data->raydir.x);
	if (data->raydir.y == 0)
		deltadist->y = 1e30;
	else
		deltadist->y = fabs(1 / data->raydir.y);
}

void	calc_sidedist(t_data *data, t_dpos *sidedist, t_coord *map,
			t_dpos deltadist)
{
	if (data->raydir.x < 0)
		sidedist->x = (data->map_data.player_pos_x - map->x) * deltadist.x;
	else
		sidedist->x = (map->x + 1.0 - data->map_data.player_pos_x)
			* deltadist.x;
	if (data->raydir.y < 0)
		sidedist->y = (data->map_data.player_pos_y - map->y) * deltadist.y;
	else
		sidedist->y = (map->y + 1.0 - data->map_data.player_pos_y)
			* deltadist.y;
}

void	init_step(t_data *data, t_coord *step)
{
	if (data->raydir.x < 0)
		step->x = -1;
	else
		step->x = 1;
	if (data->raydir.y < 0)
		step->y = -1;
	else
		step->y = 1;
}

void	init_perp_wall_d(int side, double *perp_wall_d, t_dpos sidedist,
			t_dpos deltadist)
{
	if (side == 0)
		*perp_wall_d = (sidedist.x - deltadist.x);
	else
		*perp_wall_d = (sidedist.y - deltadist.y);
}

void	calc_dist(t_data *data, t_coord *map, int *side, double *perp_wall_d)
{
	t_dpos	sidedist;
	t_dpos	deltadist;
	t_coord	step;

	calc_deltadist(data, &deltadist);
	init_step(data, &step);
	calc_sidedist(data, &sidedist, map, deltadist);
	while (1)
	{
		if (sidedist.x < sidedist.y)
		{
			sidedist.x += deltadist.x;
			map->x += step.x;
			*side = 0;
		}
		else
		{
			sidedist.y += deltadist.y;
			map->y += step.y;
			*side = 1;
		}
		if (!iswall(&data->map_data, map->y, map->x))
			break ;
	}
	init_perp_wall_d(*side, perp_wall_d, sidedist, deltadist);
}

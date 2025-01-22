/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:20:01 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/13 13:20:02 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	parse_mmap(t_data *data)
{
	t_coord	checker;
	t_coord	pen;

	checker = create_coord(0, 0);
	pen = create_coord(TILE, TILE);
	while (checker.y < data->map_data.height)
	{
		while (checker.x < data->map_data.width)
		{
			draw_tile(data, data->map_data.map[checker.y][checker.x], &pen);
			pen.x += TILE;
			checker.x++;
		}
		pen.x = TILE;
		pen.y += TILE;
		checker.x = 0;
		checker.y++;
	}
}

void	draw_tile(t_data *data, char c, t_coord *pen)
{
	t_coord	limit;

	limit = create_coord(pen->x + TILE, pen->y + TILE);
	while (pen->y < limit.y)
	{
		while (pen->x < limit.x)
		{
			if (is_onmap(c))
				put_pixel(data->img, pen->x, pen->y, select_color(c));
			pen->x++;
		}
		pen->x = limit.x - TILE;
		pen->y++;
	}
	pen->y = limit.y - TILE;
}

int	select_color(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (0xFF0000);
	else if (c == '1')
		return (0x00FF00);
	else
		return (0xFFFFFF);
}

int	is_onmap(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

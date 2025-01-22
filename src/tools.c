/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:13:33 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/13 13:13:34 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	display_map_data(t_map_data *map_data)
{
	int	x;
	int	y;

	printf("\n\n");
	y = 0;
	while (y < map_data->height)
	{
		x = 0;
		while (x < map_data->width)
		{
			if (map_data->map[y][x] == '1')
				printf("\033[31m%c\033[0m", map_data->map[y][x]);
			else if (map_data->map[y][x] == 'F')
				printf("\033[32m%c\033[0m", map_data->map[y][x]);
			else if (map_data->map[y][x] == 'N' || map_data->map[y][x] == 'W'
					|| map_data->map[y][x] == 'E' || map_data->map[y][x] == 'S')
				printf("\033[1;35m%c\033[0m", map_data->map[y][x]);
			else
				printf("%c", map_data->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("\n\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:11:55 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/13 13:12:00 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	map_free_after_flood_fill(t_map_data *map_data)
{
	int	nbr_of_lines;

	nbr_of_lines = 0;
	if (map_data->map != NULL)
	{
		while (nbr_of_lines < map_data->height)
		{
			free(map_data->map[nbr_of_lines]);
			map_data->map[nbr_of_lines] = NULL;
			nbr_of_lines++;
		}
		free(map_data->map);
	}
	return (1);
}

void	flood_map(t_map_data *map_data, int x, int y)
{
	if (x < 0 || y < 0 || x >= map_data->width || y >= map_data->height)
	{
		map_data->map_error = 1;
		return ;
	}
	if (map_data->map[y][x] == '0')
	{
		if ((x > 0 && map_data->map[y][x - 1] == ' ')
			|| (x < map_data->width - 1 && map_data->map[y][x + 1] == ' ')
			|| (y > 0 && map_data->map[y - 1][x] == ' ')
			|| (y < map_data->height - 1 && map_data->map[y + 1][x] == ' '))
		{
			map_data->map_error = 1;
			return ;
		}
	}
	if (map_data->map[y][x] == '1' || map_data->map[y][x] == 'F')
		return ;
	map_data->map[y][x] = 'F';
	flood_map(map_data, x, y + 1);
	flood_map(map_data, x, y - 1);
	flood_map(map_data, x + 1, y);
	flood_map(map_data, x - 1, y);
}

int	check_flood_fill(t_map_data *map_data)
{
	int	x;
	int	y;

	map_data->map_error = 0;
	y = 0;
	while (y < map_data->height)
	{
		x = -1;
		while (++x < map_data->width)
		{
			if (map_data->map[y][x] == '0')
			{
				flood_map(map_data, x, y);
				if (map_data->map_error == 1)
					return (printf("Error: map is not closed\n"), 0);
				x = 0;
				y = 0;
				break ;
			}
		}
		if (map_data->map_error == 1)
			break ;
		y++;
	}
	return (1);
}

int	routine_floodfill(t_map_data *map_data, char *map_file)
{
	if (!create_map_for_game(map_data, map_file))
	{
		return (0);
	}
	if (!define_check_pos(map_data))
	{
		return (0);
	}
	if (!check_flood_fill(map_data))
	{
		return (0);
	}
	if (!map_free_after_flood_fill(map_data))
	{
		return (0);
	}
	return (1);
}

int	routine_parsing(t_map_data *map_data, int ac, char **av)
{
	if (ac != 2)
	{
		ft_printf("Error: wrong number of arguments\n");
		return (0);
	}
	if (!check_extension_file_name(av[1], 1))
	{
		ft_printf("Error: invalid file extension\n");
		return (0);
	}
	if (does_file_exist(av[1]))
	{
		ft_printf("Error: the file does not exist\n");
		return (0);
	}
	printf("routine parsing MAP FILE %s\n", av[1]);
	if (!routine_floodfill(map_data, av[1]))
	{
		free_map_data(map_data);
		printf("Error: flood fill check failed\n");
		return (0);
	}
	printf("routine parsing MAP FILE %s\n", av[1]);
	return (1);
}

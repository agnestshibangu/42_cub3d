/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:12:46 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/13 13:12:47 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	if_temp_null(t_map_data *map_data, char **temp)
{
	int		y;

	if (!temp)
	{
		y = 0;
		while (y < map_data->height)
		{
			free(temp[y]);
			y++;
		}
		free(temp);
		return (0);
	}
	return (1);
}

void	allocate_verline_data(t_data *data)
{
	data->verl_inf = malloc(sizeof(t_verl_inf));
}

char	**manage_temp(t_map_data *map_data, char *line)
{
	char	**temp;
	int		i;

	i = 0;
	temp = (char **)malloc(sizeof(char *) * (map_data->height + 1));
	if (!temp)
		return (0);
	temp[map_data->height - 1] = NULL;
	while (i < map_data->height - 1)
	{
		temp[i] = map_data->map[i];
		i++;
	}
	temp[i] = ft_strdup(line);
	if (!temp[i])
	{
		if_temp_null(map_data, temp);
		return (NULL);
	}
	return (temp);
}

int	define_player_pos(t_map_data *map_data)
{
	int	x;
	int	y;

	y = 0;
	while (y < map_data->height)
	{
		x = 0;
		while (x < map_data->width - 1)
		{
			if (map_data->map[y][x] == 'W' || map_data->map[y][x] == 'E'
				|| map_data->map[y][x] == 'S' || map_data->map[y][x] == 'N')
			{
				map_data->player_pos_x = y + 0.5;
				map_data->player_pos_y = x + 0.5;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	define_check_pos(t_map_data *map_data)
{
	int	x;
	int	y;

	y = 0;
	while (y < map_data->height)
	{
		x = 0;
		while (x < map_data->width - 1)
		{
			if (map_data->map[y][x] == '0')
			{
				map_data->check_pos_x = x;
				map_data->check_pos_y = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

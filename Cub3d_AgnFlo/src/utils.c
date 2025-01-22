/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:13:37 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/13 13:19:23 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	clean_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (&data->texture[i])
		{
			if (data->texture[i].path)
			{
				free(data->texture[i].path);
				data->texture[i].path = NULL;
			}
		}
		i++;
	}
	free_img(data);
	free_color(data);
	free_map_data(&data->map_data);
	free_wall(data->wall);
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	if (data->mlx)
		free(data->mlx);
	free(data);
}

void	coordswap(t_coord *a, t_coord *b)
{
	t_coord	c;

	c = *a;
	*a = *b;
	*b = c;
}

int	iswall(t_map_data *map_data, int x, int y)
{
	char	c;

	c = map_data->map[y][x];
	if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	free_color(t_data *data)
{
	free(data->colors_floor);
	free(data->colors_ceiling);
}

void	free_color_and_data(t_data *data, char *treated_line)
{
	free(treated_line);
	free_all_textures(data);
	free_color(data);
	free_map_data(&data->map_data);
	free(data);
}

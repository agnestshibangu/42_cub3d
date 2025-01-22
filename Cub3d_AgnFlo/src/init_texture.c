/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:12:41 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/13 13:12:42 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_walls(t_data *data, int i)
{
	data->texture[i].bits_per_pixels = 32;
	data->texture[i].endian = 0;
	data->texture[i].line_length = data->texture[i].width
		* (data->texture[i].bits_per_pixels / 8);
	data->texture[i].img = mlx_xpm_file_to_image(data->mlx,
			data->texture[i].path, &(data->texture[i].width),
			&(data->texture[i].height));
	data->texture[i].addr = (unsigned int *)mlx_get_data_addr(
			data->texture[i].img, &(data->texture[i].bits_per_pixels),
			&(data->texture[i].line_length), &(data->texture[i].endian));
}

void	allocate_wall(t_data *data, int i)
{
	int	num_pixels;

	if (data->wall == NULL)
		data->wall = malloc(4 * sizeof(unsigned int *));
	num_pixels = data->texture[i].width * data->texture[i].height;
	data->wall[i] = (unsigned int *)malloc(num_pixels * sizeof(unsigned int));
}

void	print_all_pixels(t_data *data, int i)
{
	unsigned int	text_i;
	int				x;
	int				y;
	unsigned int	pixel;

	y = 0;
	text_i = 0;
	while (y < data->texture[i].height)
	{
		x = 0;
		while (x < data->texture[i].width)
		{
			pixel = data->texture[i].addr[y * data->texture[i].width + x];
			data->wall[i][text_i] = (((pixel >> 16) & 0xFF) << 16)
				| (((pixel >> 8) & 0xFF) << 8) | (pixel & 0xFF);
			text_i++;
			x++;
		}
		y++;
	}
}

void	init_texture(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		init_walls(data, i);
		allocate_wall(data, i);
		print_all_pixels(data, i);
		mlx_destroy_image(data->mlx, data->texture[i].img);
		i++;
	}
}

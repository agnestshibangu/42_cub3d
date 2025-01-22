/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:19:48 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/13 13:19:49 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_img(t_data *data)
{
	if (!data->img)
	{
		data->img = malloc(sizeof(t_img));
		if (!data->img)
			return ;
	}
	data->img->img_ptr = mlx_new_image(data->mlx, SC_WIDTH, SC_HEIGHT);
	if (!data->img->img_ptr)
	{
		free(data->img);
		data->img = NULL;
		return ;
	}
	data->img->addr = mlx_get_data_addr(data->img->img_ptr,
			&data->img->bpp, &data->img->line_length, &data->img->endian);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *) pixel = color;
}

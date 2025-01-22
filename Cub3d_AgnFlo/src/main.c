/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:13:00 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/13 13:15:14 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	allocate_colors(data);
	if (!parsing(ac, av, data))
		return (ft_printf("Exiting program ...\n"),
			free_color(data), free(data), 1);
	if (!retreive_infos_textures(data, av))
		return (ft_printf("Exiting program ...\n"), free_color(data),
			free_all_textures(data), free(data), 1);
	init_var(data);
	init_win(data);
	init_map(data);
	allocate_verline_data(data);
	init_img(data);
	init_texture(data);
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(data->mlx_win, 6, 1L << 6, handle_mouse_move, data);
	mlx_hook(data->mlx_win, 17, 0, close_and_clean, data);
	mlx_loop_hook(data->mlx, loop_routine, data);
	mlx_loop(data->mlx);
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode < 256 && keycode > 2)
		data->keys[keycode] = 1;
	else
	{
		if (keycode == XK_Left)
			data->keys[0] = 1;
		if (keycode == XK_Right)
			data->keys[1] = 1;
		if (keycode == XK_Escape)
			data->keys[2] = 1;
	}
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode < 256 && keycode > 2)
		data->keys[keycode] = 0;
	else
	{
		if (keycode == XK_Left)
			data->keys[0] = 0;
		if (keycode == XK_Right)
			data->keys[1] = 0;
		if (keycode == XK_Escape)
			data->keys[2] = 0;
	}
	return (0);
}

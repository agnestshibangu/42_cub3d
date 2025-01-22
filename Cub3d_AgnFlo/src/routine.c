/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:13:29 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/13 13:16:17 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	loop_routine(t_data *data)
{
	if (data->keys[2])
		close_and_clean(data);
	if (data->keys[XK_w])
		forward(&data->map_data);
	if (data->keys[XK_s])
		backward(&data->map_data);
	if (data->keys[XK_a])
		strafe_left(&data->map_data);
	if (data->keys[XK_d])
		strafe_right(&data->map_data);
	if (data->keys[0])
		rotate(&data->map_data.player, ROT_SPEED, 1);
	if (data->keys[1])
		rotate(&data->map_data.player, ROT_SPEED, -1);
	cast_rays_and_render(data);
	parse_mmap(data);
	set_player(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img_ptr, 0, 0);
	return (1);
}

int	parsing(int ac, char **av, t_data *data)
{
	t_map_data	map_data;

	if (!routine_parsing(&map_data, ac, av))
		return (ft_printf("Error: parsing failed\n"), 0);
	ft_printf("parsing succeed... creating map\n");
	create_map_for_game(&map_data, av[1]);
	display_map_data(&map_data);
	if (!too_many_player(map_data))
	{
		free_map_data(&map_data);
		ft_printf("There is less or more than one player entity on the map.\n");
		ft_printf("please verify map settings.\n");
		return (0);
	}
	data->map_data = map_data;
	return (1);
}

int	too_many_player(t_map_data map_data)
{
	int	i;
	int	j;
	int	pcount;

	i = 0;
	pcount = 0;
	if (map_data.map == NULL)
		return (0);
	while (map_data.map[i])
	{
		j = 0;
		while (map_data.map[i][j])
		{
			if (map_data.map[i][j] == '\0')
				break ;
			if (!is_player_mmap(map_data.map[i][j]))
				pcount++;
			j++;
		}
		i++;
	}
	if (pcount != 1)
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retreive_colors2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmuller <flmuller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:08:40 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/13 13:27:54 by flmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	retreive_colors(char *treated_line, t_data *data)
{
	retrieve_colors_floor(treated_line, data);
	retrieve_colors_ceiling(treated_line, data);
}

void	check_f_c_exist(char *treated_line, t_data *data)
{
	if (strncmp(treated_line, "C ", 2) == 0)
		data->flag_color_c += 1;
	if (strncmp(treated_line, "F ", 2) == 0)
		data->flag_color_f += 1;
}

void	assign_r_g_b_floor(t_data *data, int z, int color_value)
{
	if (z == 0)
		data->colors_floor->r = (unsigned char) color_value;
	if (z == 1)
		data->colors_floor->g = (unsigned char) color_value;
	if (z == 2)
		data->colors_floor->b = (unsigned char) color_value;
}

void	assign_r_g_b_ceiling(t_data *data, int z, int color_value)
{
	if (z == 0)
		data->colors_ceiling->r = (unsigned char) color_value;
	if (z == 1)
		data->colors_ceiling->g = (unsigned char) color_value;
	if (z == 2)
		data->colors_ceiling->b = (unsigned char) color_value;
}

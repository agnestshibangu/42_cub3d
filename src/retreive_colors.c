/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retreive_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:03:28 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/13 13:08:25 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	retrieve_colors_floor(char *treated_line, t_data *data)
{
	int		i;
	int		z;

	i = 0;
	if (strncmp(treated_line, "F ", 2) == 0)
	{
		i += 2;
		while (treated_line[i] == ' ')
			i++;
		z = 0;
		while (z < 3)
		{
			treat_col_val_floor(data, &i, treated_line, z);
			z++;
		}
	}
	return (1);
}

int	retrieve_colors_ceiling(char *treated_line, t_data *data)
{
	int		i;
	int		z;

	i = 0;
	if (strncmp(treated_line, "C ", 2) == 0)
	{
		i += 2;
		while (treated_line[i] == ' ')
			i++;
		z = 0;
		while (z < 3)
		{
			treat_col_val_ceiling(data, &i, treated_line, z);
			z++;
		}
	}
	return (1);
}

void	treat_col_val_floor(t_data *data, int *i, char *treated_line, int z)
{
	char			alpha_num[4];
	unsigned int	color_value;
	int				y;

	y = 0;
	memset(alpha_num, 0, sizeof(alpha_num));
	manage_single_color(treated_line, i, &y, alpha_num);
	alpha_num[y] = '\0';
	color_value = atoi(alpha_num);
	if (color_value > 255)
	{
		free_color_and_data(data, treated_line);
		printf("error: invalid color value \n");
		exit(1);
	}
	assign_r_g_b_floor(data, z, color_value);
	if (treated_line[*i] == ',')
		(*i)++;
	else if (z != 2)
	{
		free_color_and_data(data, treated_line);
		printf("error: invalid color value \n");
		exit (1);
	}
}

void	treat_col_val_ceiling(t_data *data, int *i, char *treated_line, int z)
{
	char			alpha_num[4];
	unsigned int	color_value;
	int				y;

	y = 0;
	memset(alpha_num, 0, sizeof(alpha_num));
	manage_single_color(treated_line, i, &y, alpha_num);
	alpha_num[y] = '\0';
	color_value = atoi(alpha_num);
	if (color_value > 255)
	{
		free_color_and_data(data, treated_line);
		printf("error: invalid color value \n");
		exit(1);
	}
	assign_r_g_b_ceiling(data, z, color_value);
	if (treated_line[*i] == ',')
		(*i)++;
	else if (z != 2)
	{
		free_color_and_data(data, treated_line);
		printf("error: invalid color value \n");
		exit (1);
	}
}

void	manage_single_color(char *treated_line, int *i, int *y, char *alpha_num)
{
	while (treated_line[*i] != ',' && treated_line[*i] != '\n' && *y < 3)
	{
		alpha_num[*y] = treated_line[*i];
		(*y)++;
		(*i)++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:13:06 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/13 13:18:30 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	save_line_in_map(t_map_data *map_data, char *line)
{
	char	**temp;

	if (!line)
		return (0);
	map_data->height++;
	temp = manage_temp(map_data, line);
	if (map_data->map)
		free(map_data->map);
	map_data->map = temp;
	return (1);
}

int	is_map_line(const char *line)
{
	int	i;

	i = 0;
	if (strncmp(line, "NO", 2) == 0 || strncmp(line, "SO", 2) == 0
		|| strncmp(line, "WE", 2) == 0 || strncmp(line, "EA", 2) == 0
		|| strncmp(line, "F", 1) == 0 || strncmp(line, "C", 1) == 0)
	{
		return (0);
	}
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1'
			&& line[i] != ' ' && line[i] != '\n' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
		{
			return (2);
		}
		i++;
	}
	return (1);
}

int	create_map(t_map_data *map_data, char *map_file)
{
	int		fd;
	char	*treated_line;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
	{
		printf("error: cannot read file");
		return (0);
	}
	printf("create map MAP FILE %s\n", map_file);
	ft_memset(map_data, 0, sizeof(t_map_data));
	treated_line = get_next_line(fd);
	if (!treated_line)
		return (close(fd), 0);
	while (treated_line)
	{
		if (!treat_line(treated_line, map_data))
			return (free(treated_line), 0);
		free(treated_line);
		treated_line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	treat_line(char *treated_line, t_map_data *map_data)
{
	int		width;
	int		i;

	width = 0;
	i = 0;
	if (is_map_line(treated_line) && *treated_line != '\n')
	{
		if (is_map_line(treated_line) == 2)
			return (0);
		while (treated_line[i] != '\n' && treated_line[i] != '\0')
		{
			if (treated_line[i++] == '\t')
				width += 4;
			else
				width++;
		}
		treated_line[i] = '\0';
		if (map_data->width < width)
			map_data->width = width;
		save_line_in_map(map_data, treated_line);
	}
	return (1);
}

int	create_map_for_game(t_map_data *map_data, char *map_file)
{
	if (!create_map(map_data, map_file))
	{
		ft_printf("Error: Failed to create map\n");
		return (0);
	}
	else
	{
		return (1);
	}
}

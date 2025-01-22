/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:20:17 by agtshiba          #+#    #+#             */
/*   Updated: 2025/01/13 13:20:19 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_pos	create_pos(float x, float y)
{
	t_pos	point;

	point.x = x;
	point.y = y;
	return (point);
}

t_coord	create_coord(int x, int y)
{
	t_coord	point;

	point.x = x;
	point.y = y;
	return (point);
}

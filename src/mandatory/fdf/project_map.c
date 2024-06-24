/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 06:23:14 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/24 08:54:11 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file project_map.c
 * @dontinclude project_map.c
 * @line /\* *********
 * @until /\* *********
 */

#include <math.h>
#include "../fdf.h"
#include "map.h"

/**
 * @brief Apply offset to projected coordinates
 * 
 * @param map 
 * @param x_offset Offset required for left-most x to be zero
 * @param y_offset Offset required for top-most y to be zero
 */
static void	apply_offset(t_map map, int x_offset, int y_offset)
{
	int	x;
	int	y;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			map.point[y][x].projected[0] -= x_offset;
			map.point[y][x].projected[1] -= y_offset;
			x++;
		}
		y++;
	}
}

/**
 * @brief Generate coordinates from map input and scale via isometric projection
 * 
 * @param map 
 * @param scale 
 */
static void	project(t_map map, int scale)
{
	static double	cs_30[2] = {0, 0};
	int				x;
	int				y;
	int				y_offset;

	if (cs_30[0] == 0)
		cs_30[0] = cos(30 * M_PI / 180);
	if (cs_30[1] == 0)
		cs_30[1] = sin(30 * M_PI / 180);
	y_offset = 0;
	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			map.point[y][x].projected[0] = (x - y) * scale * cs_30[0];
			map.point[y][x].projected[1] = (x + y) * scale * cs_30[1]
				- map.point[y][x].height * scale;
			if (map.point[y][x++].projected[1] < y_offset)
				y_offset = map.point[y][x - 1].projected[1];
		}
		y++;
	}
	apply_offset(map, map.point[map.height - 1][0].projected[0], y_offset);
}

/**
 * @brief Get boundaries of projected map
 * 
 * @param map 
 * @param size 
 */
static void	calc_size(t_map map, int *size)
{
	int	x;
	int	y;

	size[0] = map.point[0][map.width - 1].projected[0]
		- map.point[map.height - 1][0].projected[0];
	size[1] = 0;
	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (map.point[y][x].projected[1] > size[1])
				size[1] = map.point[y][x].projected[1];
			x++;
		}
		y++;
	}
	size[1] += 1;
}

/**
 * @brief Project map and attempt to automatically scale to viewport.
 * 
 * @param map 
 * @param size
 * @retval int 0 if scaling was successful, 1 if map was too large
 */
int	project_map(t_map map, int *size)
{
	int	viewport[2];
	int	scale;

	mlx_get_monitor_size(0, &viewport[0], &viewport[1]);
	viewport[0] *= FDF_TARGET_VIEWPORT_PERCENT;
	viewport[1] *= FDF_TARGET_VIEWPORT_PERCENT;
	scale = viewport[1];
	if (viewport[0] < scale)
		scale = viewport[0];
	scale = scale
		/ (sqrt(map.width * map.width + map.height * map.height)
			* atan(sin(30 * M_PI / 180)));
	if (scale < 1)
		scale = 1;
	project(map, scale);
	calc_size(map, size);
	while (size[0] > viewport[0] || size[1] > viewport[1])
	{
		if (scale == 1)
			return (1);
		project(map, --scale);
		calc_size(map, size);
	}
	return (0);
}

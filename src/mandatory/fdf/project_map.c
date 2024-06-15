/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 06:23:14 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/15 09:26:13 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../fdf.h"
#include "map.h"

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

static void	project(t_map map, int scale)
{
	int	x;
	int	y;
	int	y_offset;

	y_offset = 0;
	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			map.point[y][x].projected[0]
				= (x - y) * scale * cos(30 * M_PI / 180);
			map.point[y][x].projected[1]
				= (x + y) * scale * sin(30 * M_PI / 180)
				- map.point[y][x].height * scale;
			if (map.point[y][x].projected[1] < y_offset)
				y_offset = map.point[y][x].projected[1];
			x++;
		}
		y++;
	}
	apply_offset(map, map.point[map.height - 1][0].projected[0], y_offset);
}

static int	calc_size(t_map map, int *size, int *viewport)
{
	int	x;
	int	y;

	size[0] = map.point[0][map.width - 1].projected[0] - map.point[map.height - 1][0].projected[0];
	if (size[0] > viewport[0])
		return (1);
	size[1] = 0;
	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (map.point[y][x].projected[1] > size[1])
				size[1] = map.point[y][x].projected[1];
			if ((size[1] + 1) > viewport[1])
				return (1);
			x++;
		}
		y++;
	}
	size[1] = size[1] + 1;
	return (0);
}

void	project_map(t_loop_data *d, int *size, int *viewport)
{
	int	scale;

	scale = viewport[1];
	if (viewport[0] < scale)
		scale = viewport[0];
	scale = scale
		/ (sqrt(d->map.width * d->map.width + d->map.height * d->map.height)
			* atan(sin(45 * M_PI / 180)));
	if (!scale)
		scale = 1;
	project(d->map, scale);
	while (scale > 1 && calc_size(d->map, size, viewport))
	{
		scale--;
		project(d->map, scale);
	}
}

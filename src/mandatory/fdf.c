/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:38:21 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/13 08:56:17 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <MLX42.h>
#include <ft_printf.h>
#include "fdf.h"
#include "fdf/map.h"

void    iso(int *p_3d, int *p_2d);
int 	fdf_mlx(t_map map, int *offset, int *size);

static void	project(t_map map, int scale)
{
	int	x;
	int	y;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			iso((int []){x * scale, y * scale, map.point[y][x].height * scale},
				map.point[y][x].projected);
			x++;
		}
		y++;
	}
}

static void	calc_offset(t_map map, int *offset)
{
	int	x;
	int	y;

	offset[0] = map.point[map.height - 1][0].projected[0];
	offset[1] = 0;
	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (map.point[y][x].projected[1] < offset[1])
				offset[1] = map.point[y][x].projected[1];
			x++;
		}
		y++;
	}
}

static void	calc_size(t_map map, int *offset, int *size)
{
	int	x;
	int	y;

	size[0] = map.point[0][map.width - 1].projected[0] - map.point[map.height - 1][0].projected[0];
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
	size[1] = size[1] - offset[1] + 1;
}

static int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static int	pythagorean(int a, int b)
{
	return (sqrt((a * a) + (b * b)));
}

int	fdf(t_map map)
{
	int			offset[2];
	int			size[2];

	project(map, max(1, min(FDF_MAX_SCALE, min(FDF_MAX_WIDTH, FDF_MAX_HEIGHT) / pythagorean(map.width, map.height))));
	calc_offset(map, offset);
	calc_size(map, offset, size);
	/*if (size[0] > FDF_MAX_WIDTH)
	{
		ft_printf("%>Map exceeds max width with scale %d\n", 2, FDF_SCALE);
		return (1);
	}
	if (size[1] > FDF_MAX_HEIGHT)
	{
		ft_printf("%>Map exceeds max height with scale %d\n", 2, FDF_SCALE);
		return (1);
	}*/
	return (fdf_mlx(map, offset, size));
}

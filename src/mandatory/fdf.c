/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:38:21 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/09 00:21:51 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <MLX42.h>
#include <libft.h>
#include <ft_printf.h>
#include "fdf.h"
#include "utils/map.h"

static void	keyhook(mlx_key_data_t key_data, void *arg)
{
	if (key_data.key == MLX_KEY_ESCAPE)
		mlx_close_window((mlx_t *) arg);
}

static void	bresenham(mlx_image_t *img, int *offset, int *p1, int *p2)
{
	int	x;
	int	y;
	int	err;

	err = abs(p2[0] - p1[0]) + -abs(p2[1] - p1[1]);
	x = p1[0];
	y = p1[1];
	while (1)
	{
		mlx_put_pixel(img, x - offset[0], y - offset[1], 0xFF0000FF);
		if ((err * 2 >= -abs(p2[1] - p1[1]) && x == p2[0])
			|| (err * 2 <= abs(p2[0] - p1[0]) && y == p2[1]))
			break ;
		if (err * 2 >= -abs(p2[1] - p1[1]))
		{
			err += -abs(p2[1] - p1[1]);
			x += (p1[0] < p2[0]) * 2 - 1;
		}
		if (err * 2 <= abs(p2[0] - p1[0]))
		{
			err += abs(p2[0] - p1[0]);
			y += (p1[1] < p2[1]) * 2 - 1;
		}
	}
}

static void	project(t_map map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			map.point[y][x].projected[0]
				= (x - y) * FDF_HORIZONTAL_SCALE * cos(30 * M_PI / 180);
			map.point[y][x].projected[1]
				= (x + y) * FDF_HORIZONTAL_SCALE * sin(30 * M_PI / 180)
				- map.point[y][x].height * FDF_VERTICAL_SCALE;
			x++;
		}
		y++;
	}
}

static void	mklines(t_map map, mlx_image_t *img, int *offset)
{
	int	x;
	int	y;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (x + 1 < map.width)
				bresenham(img, offset, map.point[y][x].projected,
					map.point[y][x + 1].projected);
			if (y + 1 < map.height)
				bresenham(img, offset, map.point[y][x].projected,
					map.point[y + 1][x].projected);
			x++;
		}
		y++;
	}
}


int	fdf(t_map map)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			offset[4];
	int			x;
	int			y;

	project(map);
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
	offset[2] = map.point[0][map.width - 1].projected[0] - map.point[map.height - 1][0].projected[0];
	offset[3] = 0;
	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (map.point[y][x].projected[1] > offset[3])
				offset[3] = map.point[y][x].projected[1];
			x++;
		}
		y++;
	}
	offset[3] = offset[3] - offset[1];
	mlx = mlx_init(offset[2], offset[3], "Gungus", 0);
	if (!mlx)
	{
		ft_printf("%>mlx_init() failed:%s\n", 2, mlx_strerror(mlx_errno));
		return (1);
	}
	img = mlx_new_image(mlx, FDF_WIDTH, FDF_HEIGHT);
	if (!img)
	{
		ft_printf("%>mlx_new_image() failed:%s\n", 2, mlx_strerror(mlx_errno));
		return (1);
	}
	mklines(map, img, offset);
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
	{
		ft_printf("%>mlx_image_to_window() failed:%s\n", 2, mlx_strerror(mlx_errno));
		return (1);
	}
	mlx_key_hook(mlx, keyhook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

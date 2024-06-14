/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 07:32:01 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/14 10:15:24 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <MLX42.h>
#include <ft_printf.h>
#include "../fdf.h"
#include "map.h"

void	draw_line(mlx_image_t *img, int *offset, int *p1, int *p2);

static void	keyhook(mlx_key_data_t key_data, void *arg)
{
	if (key_data.key == MLX_KEY_ESCAPE)
		mlx_close_window((mlx_t *) arg);
}

static void	fdf_lines(t_map map, mlx_image_t *img, int *offset)
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
				draw_line(img, offset, map.point[y][x].projected,
					map.point[y][x + 1].projected);
			if (y + 1 < map.height)
				draw_line(img, offset, map.point[y][x].projected,
					map.point[y + 1][x].projected);
			x++;
		}
		free(map.point[y]);
		y++;
	}
}

static void	fdf_row(void *data)
{
	int			x;
	int			starting_y;
	t_loop_data	*d;

	d = (t_loop_data *) data;
	if (d->cury == d->map.height)
		return ;
	starting_y = d->cury;
	while ((d->cury < d->map.height) && (d->cury - starting_y) < FDF_ROWS_PER_ITERATION)
	{
		x = 0;
		while (x < d->map.width)
		{
			if (x + 1 < d->map.width)
				draw_line(d->img, d->offset, d->map.point[d->cury][x].projected,
					d->map.point[d->cury][x + 1].projected);
			if (d->cury + 1 < d->map.height)
				draw_line(d->img, d->offset, d->map.point[d->cury][x].projected,
					d->map.point[d->cury + 1][x].projected);
			x++;
		}
		d->cury++;
	}
}

int fdf_mlx(t_loop_data	ld)
{
	mlx_t		*mlx;

    mlx = mlx_init(ld.size[0], ld.size[1], "fdf", 0);
	if (!mlx)
	{
		ft_printf("%>mlx_init() failed:%s\n", 2, mlx_strerror(mlx_errno));
		return (1);
	}
	ld.img = mlx_new_image(mlx, ld.size[0], ld.size[1]);
	if (!ld.img)
	{
		ft_printf("%>mlx_new_image() failed:%s\n", 2, mlx_strerror(mlx_errno));
		return (1);
	}
	if (mlx_image_to_window(mlx, ld.img, 0, 0) == -1)
	{
		ft_printf("%>mlx_image_to_window() failed:%s\n", 2, mlx_strerror(mlx_errno));
		return (1);
	}
	mlx_loop_hook(mlx, fdf_row, &ld);
	mlx_key_hook(mlx, keyhook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

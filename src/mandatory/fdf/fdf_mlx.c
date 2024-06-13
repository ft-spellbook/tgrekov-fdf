/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 07:32:01 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/13 08:37:07 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <MLX42.h>
#include <ft_printf.h>
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

int fdf_mlx(t_map map, int *offset, int *size)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

    mlx = mlx_init(size[0], size[1], "fdf", 0);
	if (!mlx)
	{
		ft_printf("%>mlx_init() failed:%s\n", 2, mlx_strerror(mlx_errno));
		return (1);
	}
	img = mlx_new_image(mlx, size[0], size[1]);
	if (!img)
	{
		ft_printf("%>mlx_new_image() failed:%s\n", 2, mlx_strerror(mlx_errno));
		return (1);
	}
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
	{
		ft_printf("%>mlx_image_to_window() failed:%s\n", 2, mlx_strerror(mlx_errno));
		return (1);
	}
	fdf_lines(map, img, offset);
	mlx_key_hook(mlx, keyhook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

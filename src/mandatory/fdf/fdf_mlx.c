/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 07:32:01 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/24 08:50:27 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file fdf_mlx.c
 * @dontinclude fdf_mlx.c
 * @line /\* *********
 * @until /\* *********
 */

#include <stdlib.h>
#include <MLX42.h>
#include <ft_printf.h>
#include "../fdf.h"
#include "map.h"

void	draw_line(mlx_image_t *img, int x1, int y1, int *p2);
int		project_map(t_map map, int *size);

/**
 * @brief Runs when a key is pressed to check whether the escape key was used,
 * so the window can be closed
 * 
 * @param key_data 
 * @param arg Mlx instance pointer
 */
static void	keyhook(mlx_key_data_t key_data, void *arg)
{
	if (key_data.key == MLX_KEY_ESCAPE)
		mlx_close_window((mlx_t *) arg);
}

/**
 * @brief Checks if adjacent points are available, and draws lines
 * to them
 * 
 * @param img Mlx image pointer
 * @param map 
 * @param x 
 * @param y 
 */
static void	lines_from_point(mlx_image_t *img, t_map map, int x, int y)
{
	if (x < (map.width - 1))
		draw_line(img,
			map.point[y][x].projected[0], map.point[y][x].projected[1],
			map.point[y][x + 1].projected);
	if (y < (map.height - 1))
		draw_line(img,
			map.point[y][x].projected[0], map.point[y][x].projected[1],
			map.point[y + 1][x].projected);
}

/**
 * @brief Draw rows in between frames if the image isn't complete
 * 
 * @param data @ref s_loop_data "loop data"
 */
static void	fdf_row(void *data)
{
	int			x;
	int			init_y;
	t_loop_data	*d;

	d = (t_loop_data *) data;
	if (d->y == d->map.height)
		return ;
	init_y = d->y;
	while ((d->y < d->map.height) && (d->y - init_y) < FDF_ROWS_PER_ITERATION)
	{
		x = 0;
		while (x < d->map.width)
			lines_from_point(d->img, d->map, x++, d->y);
		d->y++;
	}
}

/**
 * @brief Bulk of mlx functions used in fdf, to set up the key press and drawing
 * hooks, set up the image, start the rendering, etc
 * 
 * @param mlx
 * @param d 
 * @param size Window size to resize to
 * @retval int 
 */
static int	fdf_mlx(mlx_t *mlx, t_loop_data d, int *size)
{
	mlx_set_window_size(mlx, size[0], size[1]);
	mlx_set_window_pos(mlx, 0, 0);
	d.img = mlx_new_image(mlx, size[0], size[1]);
	if (!d.img)
	{
		ft_printf("%>mlx_new_image() failed: %s\n", 2, mlx_strerror(mlx_errno));
		return (1);
	}
	if (mlx_image_to_window(mlx, d.img, 0, 0) == -1)
	{
		ft_printf("%>mlx_image_to_window() failed: %s\n",
			2, mlx_strerror(mlx_errno));
		mlx_delete_image(mlx, d.img);
		return (1);
	}
	mlx_loop_hook(mlx, fdf_row, &d);
	mlx_key_hook(mlx, keyhook, mlx);
	d.y = 0;
	mlx_loop(mlx);
	mlx_delete_image(mlx, d.img);
	if (mlx_errno)
		ft_printf("%>MLX error with unknown source: %s\n",
			2, mlx_strerror(mlx_errno));
	return (mlx_errno);
}

/**
 * @brief Initialize mlx, run map projection and scaling,
 * execute mlx, and cleanup
 * 
 * @param map 
 * @retval int Exit status, 0 on success
 */
int	fdf(t_map map)
{
	mlx_t		*mlx;
	t_loop_data	d;
	int			size[2];
	int			status;

	mlx = mlx_init(1, 1, FDF_WINDOW_TITLE, 0);
	if (!mlx)
	{
		ft_printf("%>mlx_init() failed:%s\n", 2, mlx_strerror(mlx_errno));
		return (0);
	}
	d.map = map;
	if (project_map(map, size))
	{
		ft_printf("%>Map too big\n", 2);
		status = 1;
	}
	else
		status = fdf_mlx(mlx, d, size);
	mlx_terminate(mlx);
	return (status);
}

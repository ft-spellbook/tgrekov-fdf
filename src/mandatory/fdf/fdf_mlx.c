/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 07:32:01 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/15 07:07:15 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <MLX42.h>
#include <ft_printf.h>
#include "../fdf.h"
#include "map.h"

void	draw_line(t_loop_data *d, int x1, int y1, int x2, int y2);
void	project_map(t_loop_data *d, int *size, int *viewport);


static void	keyhook(mlx_key_data_t key_data, void *arg)
{
	if (key_data.key == MLX_KEY_ESCAPE)
		mlx_close_window((mlx_t *) arg);
}

static void	lines_from_point(t_loop_data *d, int x, int y)
{
	t_point	**p;

	p = d->map.point;
	if (x < (d->map.width - 1))
		draw_line(d, p[y][x].projected[0], p[y][x].projected[1], 
			p[y][x + 1].projected[0], p[y][x + 1].projected[1]);
	if (y < (d->map.height - 1))
		draw_line(d, p[y][x].projected[0], p[y][x].projected[1],
			p[y + 1][x].projected[0], p[y + 1][x].projected[1]);
}

static void	fdf_row(void *data)
{
	int			x;
	int			starting_y;
	t_loop_data	*d;

	d = (t_loop_data *) data;
	if (d->y == d->map.height)
		return ;
	starting_y = d->y;
	while ((d->y < d->map.height) && (d->y - starting_y) < FDF_ROWS_PER_ITERATION)
	{
		x = 0;
		while (x < d->map.width)
			lines_from_point(d, x++, d->y);
		d->y++;
	}
}

static int	_fdf_mlx(mlx_t *mlx, t_loop_data d, int *size)
{
	mlx_set_window_size(mlx, size[0], size[1]);
	mlx_set_window_pos(mlx, 0, 0);
	d.img = mlx_new_image(mlx, size[0], size[1]);
	if (!d.img)
	{
		ft_printf("%>mlx_new_image() failed:%s\n", 2, mlx_strerror(mlx_errno));
		mlx_terminate(mlx);
		return (1);
	}
	if (mlx_image_to_window(mlx, d.img, 0, 0) == -1)
	{
		ft_printf("%>mlx_image_to_window() failed:%s\n", 2, mlx_strerror(mlx_errno));
		mlx_delete_image(mlx, d.img);
		mlx_terminate(mlx);
		return (1);
	}
	mlx_loop_hook(mlx, fdf_row, &d);
	mlx_key_hook(mlx, keyhook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, d.img);
	mlx_terminate(mlx);
	return (0);
}

int	fdf_mlx(t_map map)
{
	mlx_t		*mlx;
	t_loop_data	d;
	int			viewport[2];
	int			size[2];

	mlx = mlx_init(1, 1, FDF_WINDOW_TITLE, 0);
	if (!mlx)
	{
		ft_printf("%>mlx_init() failed:%s\n", 2, mlx_strerror(mlx_errno));
		return (0);
	}
	mlx_get_monitor_size(0, &viewport[0], &viewport[1]);
	viewport[0] *= 0.95;
	viewport[1] *= 0.95;
	d.map = map;
	project_map(&d, size, viewport);
	d.y = 0;
    return (_fdf_mlx(mlx, d, size));
}

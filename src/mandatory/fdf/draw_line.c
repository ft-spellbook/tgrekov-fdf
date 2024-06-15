/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:17:39 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/15 08:45:48 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include "../utils/utils.h"
#include "map.h"

void	draw_line(t_loop_data *d, int x1, int y1, int x2, int y2)
{
    int dx;
    int dy;
	int	err;
	int	dir[2];

    dx = abs(x2 - x1);
    dy = -abs(y2 - y1);
	err = dx + dy;
	dir[0] = (x1 < x2) * 2 - 1;
	dir[1] = (y1 < y2) * 2 - 1;
	while (!(err * 2 >= dy && x1 == x2) && !(err * 2 <= dx && y1 == y2))
	{
		mlx_put_pixel(d->img, x1, y1, 0xFF0000FF);
		if (err * 2 >= dy)
		{
			err += dy;
			x1 += dir[0];
		}
		if (err * 2 <= dx)
		{
			err += dx;
			y1 += dir[1];
		}
	}
}

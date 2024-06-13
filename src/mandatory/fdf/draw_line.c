/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:17:39 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/13 08:20:18 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include "../utils/utils.h"
#include "map.h"

void	draw_line(mlx_image_t *img, int *offset, int *p1, int *p2)
{
	int	x;
	int	y;
    int dx;
    int dy;
	int	err;

	x = p1[0];
	y = p1[1];
    dx = abs(p2[0] - x);
    dy = -abs(p2[1] - y);
	err = dx + dy;
	while (!(err * 2 >= dy && x == p2[0]) && !(err * 2 <= dx && y == p2[1]))
	{
		mlx_put_pixel(img, x - offset[0], y - offset[1], 0xFF0000FF);
		if (err * 2 >= dy)
		{
			err += dy;
			x += (p1[0] < p2[0]) * 2 - 1;
		}
		if (err * 2 <= dx)
		{
			err += dx;
			y += (p1[1] < p2[1]) * 2 - 1;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:17:39 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/15 11:21:46 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include "../utils/utils.h"

void	draw_line(mlx_image_t *img, int x1, int y1, int *p2)
{
	int	dx;
	int	dy;
	int	err;
	int	dir[2];

	dx = abs(p2[0] - x1);
	dy = -abs(p2[1] - y1);
	err = dx + dy;
	dir[0] = (x1 < p2[0]) * 2 - 1;
	dir[1] = (y1 < p2[1]) * 2 - 1;
	while (!(err * 2 >= dy && x1 == p2[0]) && !(err * 2 <= dx && y1 == p2[1]))
	{
		mlx_put_pixel(img, x1, y1, 0xFF0000FF);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:38:21 by tgrekov           #+#    #+#             */
/*   Updated: 2024/05/20 12:02:37 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <libft.h>
#include <ft_printf.h>
#include "utils/map.h"

static void	keyhook(mlx_key_data_t key_data, void *arg)
{
	if (key_data.key == MLX_KEY_ESCAPE)
		mlx_close_window((mlx_t *) arg);
}

int	fdf(t_map map)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	(void) map;
	mlx = mlx_init(1366, 768, "Gungus", true);
	if (!mlx)
	{
		ft_printf("%>mlx_init() failed:%s\n", 2, mlx_strerror(mlx_errno));
		return (1);
	}
	img = mlx_new_image(mlx, 1366, 768);
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
	mlx_key_hook(mlx, keyhook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

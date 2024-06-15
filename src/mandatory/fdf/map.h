/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 08:48:52 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/15 08:45:25 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

#include <MLX42.h>

typedef struct s_point
{
	int	height;
	int	projected[2];
}		t_point;

typedef struct s_map
{
	int		width;
	int		height;
	t_point	**point;
}	t_map;

typedef struct s_loop_data
{
	t_map		map;
	mlx_image_t	*img;
	int			y;
}	t_loop_data;	

#endif
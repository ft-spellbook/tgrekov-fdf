/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 08:48:52 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/24 06:19:19 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file map.h
 * @dontinclude map.h
 * @line /\* *********
 * @until /\* *********
 */

#ifndef MAP_H
# define MAP_H

# include <MLX42.h>

/**
 * @struct s_point
 * @brief Map point
 * @typedef t_point
 * @copybrief s_point
 * @property s_point::height
 * @brief Height extracted from map file
 * @property s_point::projected
 * @brief Projected coordinates for this point
 */
typedef struct s_point
{
	int	height;
	int	projected[2];
}		t_point;

/**
 * @struct s_map
 * @brief Map data
 * @typedef t_map
 * @copybrief s_map
 * @property s_map::width
 * @brief Number of columns in the map
 * @property s_map::height
 * @brief Number of rows in the map
 * @property s_map::point
 * @brief 2d array of @ref s_point "points" in [y][x] order
 */
typedef struct s_map
{
	int		width;
	int		height;
	t_point	**point;
}	t_map;

/**
 * @struct s_loop_data
 * @brief Data structure passed to the drawing loop
 * @typedef t_loop_data
 * @copybrief s_loop_data
 * @property s_loop_data::map
 * @brief @ref s_map "Map"
 * @property s_loop_data::img
 * @brief Pointer to mlx image on which to draw lines
 * @property s_loop_data::y
 * @brief Starting row index for the drawing loop
 */
typedef struct s_loop_data
{
	t_map		map;
	mlx_image_t	*img;
	int			y;
}	t_loop_data;	

#endif
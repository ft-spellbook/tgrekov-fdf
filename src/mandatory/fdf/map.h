/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 08:48:52 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/01 04:50:11 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

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
}		t_map;

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points_iter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:39:50 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/13 06:50:51 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void    points_iter(t_point **arr, int width,
    void (*func)(int y, int x, t_point *data))
{
    int y;
    int x;

    y = 0;
    while (arr[y])
    {
        x = 0;
        while (x < width)
        {
            func(y, x, arr[y] + x);
            x++;
        }
        y++;
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 07:21:24 by tgrekov           #+#    #+#             */
/*   Updated: 2024/05/20 09:31:33 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include "utils/map.h"
#include "utils/utils.h"

t_map	read_map(char *filename);

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc < 2)
	{
		ft_printf("%>Provide a filename containing an fdf map\n", 2);
		return (1);
	}
	map = read_map(argv[1]);
	ft_printf("%d\n", map.point[2][2]);
	if (!map.point)
		return (1);
	arr_free((void **) map.point);
}

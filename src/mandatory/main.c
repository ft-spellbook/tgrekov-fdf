/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 07:21:24 by tgrekov           #+#    #+#             */
/*   Updated: 2024/05/20 10:55:05 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include "utils/map.h"
#include "utils/utils.h"

t_map	read_map(char *filename);
int		fdf(t_map map);

int	main(int argc, char **argv)
{
	t_map	map;
	int		status;

	if (argc < 2)
	{
		ft_printf("%>Provide a filename containing an fdf map\n", 2);
		return (1);
	}
	map = read_map(argv[1]);
	if (!map.point)
		return (1);
	status = fdf(map);
	arr_free((void **) map.point);
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 07:21:24 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/21 01:28:33 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <libft.h>
#include <ft_printf.h>
#include "fdf/map.h"
#include "utils/utils.h"

t_map	read_map(int fd);
int		fdf(t_map map);

static int	open_map(char *filename)
{
	int	len;
	int	fd;

	if (filename)
		len = ft_strlen(filename);
	if (!filename || len < 4 || ft_strncmp(".fdf", filename + len - 4, 4))
	{
		ft_printf("%>Expected an FDF map file ending in .fdf\n", 2);
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		perror("open(): ");
	return (fd);
}

int	main(int argc, char **argv)
{
	t_map	map;
	int		fd;
	int		status;

	(void) argc;
	fd = open_map(argv[1]);
	if (fd == -1)
		return (1);
	map = read_map(fd);
	if (!map.point)
		return (1);
	status = fdf(map);
	arr_free((void ***) &map.point);
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 07:22:24 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/01 05:14:40 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <libft.h>
#include <ft_printf.h>
#include <get_next_line_bonus.h>
#include "utils/utils.h"
#include "utils/map.h"

static int	map_file(char *filename)
{
	int	filename_len;
	int	fd;

	filename_len = ft_strlen(filename);
	if (filename_len < 5 || ft_strncmp(".fdf", filename + filename_len - 4, 4))
	{
		ft_printf("%>Expected file name to end in .fdf\n", 2);
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	return (fd);
}

static void	split_rows(int fd, t_list **lst)
{
	char	*row;
	char	**split;
	t_list	*new_row;

	*lst = 0;
	while (1)
	{
		row = get_next_line(fd);
		if (!row && !*lst)
			return (perror("get_next_line() failed:"));
		if (!row)
			break ;
		split = ft_split(row, ' ');
		free(row);
		if (!split)
			return (perror("malloc() failed:"));
		new_row = ft_lstnew(split);
		if (!new_row)
		{
			ft_lstclear(lst, free);
			return (perror("malloc() failed:"));
		}
		ft_lstadd_back(lst, new_row);
	}
}

static int	check_width(t_list *lst, t_map *map)
{
	int	tmp;

	map->width = 0;
	map->height = 0;
	while (lst)
	{
		tmp = arr_len(lst->content);
		if (map->width && tmp != map->width)
		{
			ft_printf("%>Inconsistent row width\n", 2);
			return (1);
		}
		map->height++;
		map->width = tmp;
		lst = lst->next;
	}
	return (0);
}

static void	fill_points(t_map *map, t_list *lst)
{
	int	x;
	int	y;

	y = 0;
	while (lst)
	{
		x = 0;
		map->point[y] = malloc(sizeof(t_point) * map->width);
		if (!map->point[y])
		{
			arr_free((void **) map->point);
			return (perror("malloc() failed:"));
		}
		while (x < map->width)
		{
			map->point[y][x].height = ft_atoi(((char **) lst->content)[x]);
			x++;
		}
		y++;
		lst = lst->next;
	}
}

t_map	read_map(char *filename)
{
	t_map	map;
	int		fd;
	t_list	*lst;

	map.point = 0;
	fd = map_file(filename);
	if (fd == -1)
		return (map);
	split_rows(fd, &lst);
	if (close(fd) == -1)
		return (*(t_map *) err("close() failed:", &map));
	if (!lst)
		return (map);
	if (check_width(lst, &map))
		return (map);
	map.point = ft_calloc(map.height + 1, sizeof(t_point **));
	if (!map.point)
		return (*(t_map *) err("malloc() failed:", &map));
	fill_points(&map, lst);
	ft_lstclear(&lst, free);
	return (map);
}

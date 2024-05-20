/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 07:22:24 by tgrekov           #+#    #+#             */
/*   Updated: 2024/05/20 09:27:24 by tgrekov          ###   ########.fr       */
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

static void	fill_points(t_map *map, t_list *lst)
{
	int	x;
	int	y;

	y = 0;
	while (lst)
	{
		x = 0;
		map->point[y] = malloc(sizeof(int) * map->length);
		if (!map->point[y])
		{
			arr_free((void **) map->point);
			return (perror("malloc() failed:"));
		}
		while (x++ < map->length)
			map->point[y][x - 1] = ft_atoi(((char **) lst->content)[x - 1]);
		y++;
		lst = lst->next;
	}
}

t_map	read_map(char *filename)
{
	int		filename_len;
	int		fd;
	t_list	*lst;
	t_map	map;

	map.point = 0;
	filename_len = ft_strlen(filename);
	if (filename_len < 5 || ft_strncmp(".fdf", filename + filename_len - 4, 4))
	{
		ft_printf("%>Expected file name to end in .fdf\n", 2);
		return (map);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (*(t_map *) err("open() failed:", &map));
	split_rows(fd, &lst);
	if (!lst)
		return (map);
	map.length = arr_len(lst->content);
	map.point = ft_calloc(ft_lstsize(lst) + 1, sizeof(int *));
	if (!map.point)
		return (*(t_map *) err("malloc() failed:", &map));
	fill_points(&map, lst);
	ft_lstclear(&lst, free);
	return (map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 07:22:24 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/21 02:31:54 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file read_map.c
 * @dontinclude read_map.c
 * @line /\* *********
 * @until /\* *********
 */

#include <stdlib.h>
#include <stdio.h>
#include <libft.h>
#include <ft_printf.h>
#include <get_next_line_bonus.h>
#include "utils/utils.h"
#include "fdf/map.h"

/**
 * @brief Read rows from @p fd and place them into @p lst nodes, split on spaces
 * 
 * @param[in] fd Map file fd
 * @param[out] lst Linked list where each node contains an array of strings
 * with height,color for that index of the row
 */
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
			return (perror("get_next_line() failed (or file is empty): "));
		if (!row)
			break ;
		split = ft_split(row, ' ');
		free(row);
		if (!split)
			return (perror("malloc(): "));
		new_row = ft_lstnew(split);
		if (!new_row)
		{
			ft_lstclear(lst, free);
			return (perror("malloc(): "));
		}
		ft_lstadd_back(lst, new_row);
	}
}

/**
 * @brief Allocate @p map @ref s_point "points" and set height values
 * from @p lst
 * 
 * @param[in, out] map
 * @param[in] lst 
 */
static void	fill_points(t_map *map, t_list *lst)
{
	int	x;
	int	y;

	y = 0;
	while (lst)
	{
		x = arr_len(lst->content);
		if (map->width != x)
		{
			ft_printf("%>Inconsistent width on row %d\n", 2, y + 1);
			arr_free((void ***) &map->point);
			return ;
		}
		map->point[y] = malloc(map->width * sizeof(t_point));
		if (!map->point[y])
		{
			arr_free((void ***) &map->point);
			return (perror("malloc() failed:"));
		}
		while (x--)
			map->point[y][x].height = ft_atoi(((char **) lst->content)[x]);
		y++;
		lst = lst->next;
	}
}

/**
 * @brief Initialize @ref s_map "map" from an fdf map file pointed to by @p fd
 * 
 * @param[in] fd 
 * @retval t_map 
 */
t_map	read_map(int fd)
{
	t_map	map;
	t_list	*lst;

	map.point = 0;
	split_rows(fd, &lst);
	if (close(fd) == -1)
	{
		perror("close(): ");
		return (map);
	}
	if (!lst)
		return (map);
	map.height = ft_lstsize(lst);
	map.width = arr_len(lst->content);
	map.point = ft_calloc(map.height + 1, sizeof(t_point **));
	if (!map.point)
	{
		perror("malloc(): ");
		return (map);
	}
	fill_points(&map, lst);
	ft_lstclear(&lst, free);
	return (map);
}

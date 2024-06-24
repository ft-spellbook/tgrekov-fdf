/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 07:22:24 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/24 08:55:47 by tgrekov          ###   ########.fr       */
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
#include <errno.h>
#include <libft.h>
#include <ft_printf.h>
#include <get_next_line_bonus.h>
#include "utils/utils.h"
#include "fdf/map.h"

/**
 * @brief Wrapper around @ref arr_free "arr_free" for use with
 * @ref ft_lstclear "ft_lstclear"
 * 
 * @param arr 
 */
static void	lst_arr_free(void *arr)
{
	arr_free((void **) arr);
}

/**
 * @brief Remove trailing newline from row or print appropriate error message
 * 
 * @param[in] row 
 * @param[in] lst Linked list where each node contains an array of strings
 * with height,color for that index of the row
 * @retval char* 
 */
static char	*prep_row(char *row, t_list **lst)
{
	int		row_len;

	if (!row)
	{
		if (!*lst)
		{
			if (!errno)
				ft_printf("%>File is empty\n", 2);
			else
				perror("get_next_line()");
		}
		return (0);
	}
	row_len = ft_strlen(row);
	if (row[row_len - 1] == '\n')
		row[row_len - 1] = 0;
	return (row);
}

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
		row = prep_row(get_next_line(fd), lst);
		if (!row && !*lst)
			return ;
		if (!row)
			break ;
		split = ft_split(row, ' ');
		free(row);
		if (!split)
			return (perror("malloc()"));
		new_row = ft_lstnew(split);
		if (!new_row)
		{
			ft_lstclear(lst, lst_arr_free);
			return (perror("malloc()"));
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
 * @retval int 0 on success, positive number greater than zero otherwise
 */
static int	fill_points(t_map *map, t_list *lst)
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
			arr_free((void **) map->point);
			return (1);
		}
		map->point[y] = malloc(map->width * sizeof(t_point));
		if (!map->point[y])
		{
			arr_free((void **) map->point);
			return (*(int *) err("malloc() failed", &x));
		}
		while (x--)
			map->point[y][x].height = ft_atoi(((char **) lst->content)[x]);
		y++;
		lst = lst->next;
	}
	return (0);
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
	if (!lst)
		return (map);
	map.height = ft_lstsize(lst);
	map.width = arr_len(lst->content);
	if (map.height == 1 && map.width == 1)
	{
		ft_lstclear(&lst, lst_arr_free);
		return (*(t_map *) err("Cannot draw line from 1 point", (void *) &map));
	}
	map.point = ft_calloc(map.height + 1, sizeof(t_point **));
	if (!map.point)
	{
		ft_lstclear(&lst, lst_arr_free);
		return (*(t_map *) err("malloc()", (void *) &map));
	}
	if (fill_points(&map, lst))
		map.point = 0;
	ft_lstclear(&lst, lst_arr_free);
	return (map);
}

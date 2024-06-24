/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:05:36 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/24 04:49:14 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file err.c
 * @dontinclude err.c
 * @line /\* *********
 * @until /\* *********
 */

#include <stdio.h>
#include <errno.h>
#include <ft_printf.h>

/**
 * @brief Wrapper around <tt>perror()</tt> that always returns @p retval.
 * 
 * @param str String to pass to <tt>perror()</tt>
 * @param retval Return value
 * @retval void* @p retval
 */
void	*err(const char *str, void *retval)
{
	if (!errno)
		ft_printf("%>%s\n", 2, str);
	else
		perror(str);
	return (retval);
}

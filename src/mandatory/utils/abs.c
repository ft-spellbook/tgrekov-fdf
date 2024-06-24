/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 08:18:39 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/24 06:00:44 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file abs.c
 * @dontinclude abs.c
 * @line /\* *********
 * @until /\* *********
 */

/**
 * @brief Get absolute value of @p n
 * 
 * @param n 
 * @retval int 
 */
int	abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

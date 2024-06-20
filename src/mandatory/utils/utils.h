/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 06:08:01 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/21 01:28:09 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file src/mandatory/utils.h
 * @dontinclude src/mandatory/utils.h
 * @line /\* *********
 * @until /\* *********
 */

#ifndef UTILS_H
# define UTILS_H

void	***arr_free(void ***arr);
int		arr_len(void **arr);
void	*err(const char *str, void *retval);
int		abs(int n);

#endif
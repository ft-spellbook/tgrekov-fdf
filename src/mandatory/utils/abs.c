/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrekov <tgrekov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 08:18:39 by tgrekov           #+#    #+#             */
/*   Updated: 2024/06/13 08:19:06 by tgrekov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int abs(int n)
{
    if (n < 0)
        return (n * -1);
    return (n);
}
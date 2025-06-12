/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_degtorad.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hetya                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 23:55:05 by hetya             #+#    #+#             */
/*   Updated: 2022/02/02 23:58:42 by hetya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * this function transform degree to radians
*/
float	ft_degtorad(int degree)
{
	float	radian;

	radian = (degree * PI) / 180;
	return (radian);
}

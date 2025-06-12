/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_radtodeg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hetya                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 02:11:38 by hetya             #+#    #+#             */
/*   Updated: 2022/03/22 18:03:53 by hetya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * this function transform radians to degree
*/
int	ft_radtodeg(float radian)
{
	int	degree;

	degree = radian * (180 / PI);
	return (degree);
}

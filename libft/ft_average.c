/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_average.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hetya                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 03:37:11 by hetya             #+#    #+#             */
/*   Updated: 2022/02/08 03:46:48 by hetya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * search the average of array given in parameter
*/
int	ft_average(int *arr, int len)
{
	int	average;
	int	i;

	average = 0;
	i = -1;
	while (++i < len)
		average += arr[i];
	average /= len;
	return (average);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_is_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hetya                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 02:59:31 by hetya             #+#    #+#             */
/*   Updated: 2022/02/08 03:03:44 by hetya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * check if the stack is sort
*/
int	ft_tab_is_sort(int *tab, int len)
{
	size_t	i;

	i = 0;
	while ((int) i < len - 1)
	{
		if (tab[i] > tab[i + 1])
			return (-1);
		i++;
	}
	return (0);
}
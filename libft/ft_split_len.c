/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hetya                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 20:48:25 by hetya             #+#    #+#             */
/*   Updated: 2022/01/24 20:56:31 by hetya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * give the length a split
*/
int	split_len(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i] != NULL)
		i++;
	return (i);
}

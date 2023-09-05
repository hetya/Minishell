/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:32:02 by hetya             #+#    #+#             */
/*   Updated: 2022/03/04 15:59:24 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * malloc an area of the size count * size and setup it to zero (with bzero)
*/
void	*ft_calloc(size_t count, size_t size)
{
	size_t	bytes;
	void	*ptr;

	bytes = count * size;
	ptr = (void *)malloc(bytes);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, bytes);
	return (ptr);
}

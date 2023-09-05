/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:52:35 by hetya             #+#    #+#             */
/*   Updated: 2022/03/05 13:02:20 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * strdup allocates sufficient memory for a copy of the string s1, does the copy,
 * and returns a pointer to it
*/
char	*ft_strdup(const char *s1)
{
	char			*cpy;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	while (s1[i])
		i++;
	cpy = (char *)ft_gcalloc(sizeof(char), (i + 1));
	if (!cpy)
		return (NULL);
	while (s1[j] != '\0')
	{
		cpy[j] = s1[j];
		j++;
	}
	cpy[j] = '\0';
	return (cpy);
}

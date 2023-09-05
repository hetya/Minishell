/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:02:32 by hetya             #+#    #+#             */
/*   Updated: 2022/03/04 16:28:20 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * return a new string ptr from s. Thi new string begin a the index start of the
 * s1 string for length maximum of length
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	ptr = (char *)ft_gcalloc(sizeof(char), (len + 1));
	if (!ptr)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

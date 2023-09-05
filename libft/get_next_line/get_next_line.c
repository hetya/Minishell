/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hetya                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:09:01 by hetya           #+#    #+#             */
/*   Updated: 2021/11/22 14:10:00 by hetya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * return 1 if there is a new line in the string and 0 if not
*/
int	new_line_in(char *str)
{
	int		i;
	size_t	new_line;

	i = 0;
	new_line = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			new_line = 1;
		i++;
	}
	return (new_line);
}

/**
 * return the len of a line begin at *s and ending at a '\n' or '\0'
*/
size_t	line_len(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
	{
		i++;
	}
	if (s[i] == '\n')
		i++;
	return (i);
}

/**
 * return the new line created by the substr of ptr with the length of
 * line_len(ptr)
 * then move the next line at the front of buf and free ptr
*/
char	*new_line(char *buf, char *ptr)
{
	char			*line;

	line = ft_substr(ptr, 0, line_len(ptr));
	ft_memmove(buf, ft_strchr(buf, '\n') + 1,
		ft_strlen(ft_strchr(buf, '\n')));
	free(ptr);
	return (line);
}

/**
 * free the pointer given in parameter and
 * return NULL
*/
char	*free_ptr(char *ptr)
{
	free (ptr);
	return (NULL);
}

/**
 * use a buffer of size BUFFER_SIZE to read a line and then return it
 * for each call of the fonction, it will return the next line until there is
 * no line left
*/
char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE + 1];
	char			*ptr;
	int				size;

	ptr = NULL;
	if (buf[0] != '\0' || fd < 0)
	{
		ptr = join(ptr, buf);
		if (!ptr || fd < 0)
			return (free_ptr(ptr));
	}
	while (new_line_in(buf) == 0)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size < 0)
			return (free_ptr(ptr));
		buf[size] = '\0';
		if (size == 0)
			return (ptr);
		ptr = join(ptr, buf);
		if (!ptr)
			return (NULL);
	}
	return (new_line(buf, ptr));
}

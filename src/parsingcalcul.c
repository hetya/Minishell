/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingcalcul.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:46:55 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/16 11:51:00 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Return number of separator "|", "||", "&&" in line and outside all quote
 */
int	ft_cmdnb(char	*line)
{
	int	res;
	int	inquote;

	res = 1;
	inquote = 0;
	while (*line != '\0')
	{
		if ((*line == '"' || *line == '\'') && !inquote)
			inquote = *line;
		else if (inquote && *line == inquote)
			inquote = 0;
		if (!inquote)
		{
			if (ft_issep(line) > 1)
				res = res + 1 + (0 * (int)line++);
			else if (ft_issep(line) == 1)
				res++;
		}
		line++;
	}
	return (res);
}

/**
 * return size between start of line and firste occurence of separator
 * outside of quote
 */
int	ft_cmdlenght(char	*line)
{
	int	res;
	int	inquote;
	int	inquotenb;

	res = 0;
	inquote = 0;
	while (*line != '\0')
	{
		if ((*line == '"' || *line == '\'') && !inquote)
		{
			inquote = *line;
			inquotenb = -1;
		}
		else if (inquote && *line == inquote)
			inquote = 0;
		if (inquote)
			inquotenb++;
		else
			if (*line == '|' || (*line == '&' && *(line + 1) == '&'))
				return (res);
		line++;
		res++;
	}
	return (res);
}

int	ft_wildcardcmp(char *s1, char *s2)
{
	if ((*s2 == '.' && *s1 != '.') || !s1 || !s2)
		return (1);
	while (*s1)
	{
		if (*s1 == '*')
		{
			while (*s1 == '*')
				s1++;
			while (*s2 && *s2 != *s1)
				s2++;
			if (*s2 != *s1)
				return (1);
		}
		else
		{
			if (*s2 != *s1)
				return (1);
			s1++;
			s2++;
		}
	}
	if (*s1 || *s2)
		return (1);
	return (0);
}

int	ft_istoken(char *word)
{
	if (!ft_strncmp("<<", word, 3))
		return (1);
	if (!ft_strncmp("<", word, 2))
		return (1);
	if (!ft_strncmp(">", word, 2))
		return (1);
	if (!ft_strncmp(">>", word, 2))
		return (1);
	return (0);
}

int	ft_wildcard(t_cmddata	*res, char	*word)
{
	DIR				*d;
	struct dirent	*dir;
	char			*tmp;
	t_bool			work;

	work = 0;
	d = opendir(".");
	if (!d)
		return (0);
	dir = readdir(d);
	while (dir != NULL)
	{
		tmp = ft_strdup(dir->d_name);
		if (!ft_wildcardcmp(word, tmp))
		{
			ft_addtocmd(res, tmp);
			work = 1;
		}
		dir = readdir(d);
	}
	closedir(d);
	if (!work)
		ft_addtocmd(res, word);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:45:01 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/16 16:17:46 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_var(char	**line, int *buff, t_shell *shell, int i)
{
	char	*word;
	char	*temp;

	while ((*line)[i] && ft_strchr("\"\' $", (*line)[i]) == NULL)
		i++;
	word = ft_substr((*line), 1, i - 1);
	if (search_in_env(shell->env, word) || !ft_strcmp(word, "?"))
	{
		if (!ft_strcmp(word, "?"))
			word = ft_itoa(g_return_value);
		else
			word = ft_strtrim(search_in_env(shell->env, word), " ");
		temp = ft_gcalloc(1, ft_strlen((*line) - *buff) + ft_strlen(word) + 3);
		*(temp++) = -2;
		ft_strlcpy(temp, ((*line) - *buff), *buff + 1);
		ft_strlcpy(temp + ft_strlen(temp), word, ft_strlen(word) + 1);
		ft_strlcpy(temp + ft_strlen(temp), *line + i, ft_strlen(*line) - i + 1);
		*line = temp - 1;
		i = *buff;
		(*buff) = -1;
		return (ft_strlen(word) + i);
	}
	(*line) += ((int)ft_memset(*line, -1, i) * 0) + i - 1;
	(*buff) += i - 1;
	return (0);
}

/**
 * return char* of key when found it:
 * 					1 is <<
 * 					2 is < 
 * 					3 is >>
 * 					4 is >
 * 					5 is ||
 * 					6 is |
 * 					7 is &&
 */
char	*iskey(char **str, int buff)
{
	char	**test;
	int		i;

	test = ft_split("x.<<.<.>>.>.||.|.&&", '.');
	i = 1;
	while (test[i])
	{
		if (!ft_strncmp(test[i], *str, ft_strlen(test[i])))
		{
			if (!buff)
			{
				ft_memset(*str, -2, ft_strlen(test[i]));
				(*str) = (*str) + ft_strlen(test[i]);
			}
			return (test[i]);
		}
		i++;
	}
	return (NULL);
}

int	temp(char **line, int *inquote, t_shell *shell, int *buff)
{
	if ((*(*line) == '\"' || *(*line) == '\'' || *(*line) == -1) && !(*inquote))
	{
		*inquote = *(*line);
		*(*line) = -1;
	}
	else if ((!(*inquote) || *inquote == '"') && *(*line) == '$'
		&& !shell->checking)
		shell->count = get_env_var(line, buff, shell, 1);
	else if (*inquote && *(*line) == *inquote)
	{
		*inquote = 0;
		*(*line) = -1;
	}
	return (0);
}

char	*scan_line(t_cmddata *res, char **line, int *buff, t_shell	*shell)
{
	int		inquote;
	char	*test;

	(void)res;
	inquote = 0;
	while (*(*line) && (inquote || (*(*line) != ' ' && *(*line) != ')')))
	{
		if (!inquote && shell->count <= 0)
		{
			test = iskey(line, *buff);
			if (test && *buff)
				return (NULL);
			else if (test)
				return (test);
		}
		else
			shell->count--;
		if (shell->count <= 0 || **line == -1)
			temp(line, &inquote, shell, buff);
		(*buff)++;
		(*line)++;
	}
	return (NULL);
}

/**
 * Return word (sring between ' ' and ' ') number num in line
 */
int	ft_getword(t_cmddata *res, char	**line, char **word, t_shell *shell)
{
	int		buff;
	char	*t;

	buff = 0;
	t = 0;
	pass_space_and(res, line, 0);
	buff = 0;
	t = scan_line(res, line, &buff, shell);
	if (t)
		*word = t;
	else
		*word = ft_strdelchar(ft_strdelchar(
					ft_substr((*line) - buff, 0, buff), -1), -2);
	pass_space_and(res, line, 1);
	if (ft_strchr(ft_strdelchar(ft_substr((*line) - buff, 0, buff), -2), -1))
		return (1);
	else if (**word)
		return (1);
	else
		return (0);
}

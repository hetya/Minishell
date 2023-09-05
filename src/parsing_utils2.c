/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:14:24 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/16 16:36:08 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	preparsingutils(int *wsep, int *wtoken, char **word)
{
	if ((ft_issep(*word) && !(*wsep)) || (ft_istoken(*word) && !(*wtoken)))
	{
		ft_putstr_fd("Minishell: syntax error near '", 2);
		ft_putstr_fd(*word, 2);
		ft_putstr_fd("'\n", 2);
		g_return_value = 258;
		return (-1);
	}
	if (ft_istoken(*word))
		*wtoken = 0;
	if (!ft_istoken(*word))
		*wtoken = 1;
	if (ft_issep(*word))
		*wsep = 0;
	if (!ft_issep(*word))
		*wsep = 1;
	return (0);
}

int	preparsing(char	*line, t_shell	*shell, t_cmddata	*result)
{
	int		wsep;
	int		wtoken;
	char	*word;

	wsep = 0;
	wtoken = 1;
	shell->checking = 1;
	while (ft_getword(result, &line, &word, shell))
		if (preparsingutils(&wsep, &wtoken, &word) == -1)
			return (-1);
	shell->checking = 0;
	if (!wsep || !wtoken || result->enterbrack != result->exitbrack)
	{
		ft_putstr_fd("Minishell: error end of line\n", 2);
		g_return_value = 258;
		return (-1);
	}
	return (0);
}

void	pass_space_and(t_cmddata	*res, char **line, int n)
{
	if (!n)
	{
		while (*(*line) == ' ' || *(*line) == '(')
		{
			if (*(*line) == '(')
			{
				*(*line) = -2;
				res->enterbrack++;
			}
			(*line)++;
		}
	}
	else
	{
		while (*(*line) && (*(*line) == ' ' || *(*line) == ')'))
		{
			if (*(*line) == ')')
			{
				*(*line) = -2;
				res->exitbrack++;
			}
			(*line)++;
		}	
	}
}

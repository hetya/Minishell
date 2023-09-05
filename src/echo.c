/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hetya                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:15:51 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/09 16:20:04 by hetya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * builtin : echo
 * check if there is the -n option and return the
 * index of the last -n valid argument
*/
static int	index_line_break(char **arg)
{
	int		i;
	int		j;
	t_bool	line_break;

	line_break = 1;
	i = -1;
	while (arg[++i] != NULL && arg[i][0] == '-')
	{
		j = 1;
		if (arg[i][j] == '\0')
			return (i);
		while (arg[i][j] != '\0')
		{
			if (arg[i][j] == 'n')
				line_break = 0;
			else
			{
				line_break = 1;
				return (i);
			}
			j++;
		}
	}
	return (i);
}

/**
 * write the echo argument in STDIN add a terminating -n
 * unless there is the -n option
*/
void	echo(char **arg)
{
	int		i;
	t_bool	line_break;

	line_break = 1;
	i = index_line_break(arg);
	if (i > 0)
		line_break = 0;
	i--;
	while (arg[++i])
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1])
			ft_putstr_fd(" ", 1);
	}
	if (line_break == 1)
		ft_putstr_fd("\n", 1);
	return (exit_builtin(NULL, NULL, NULL, 0));
}

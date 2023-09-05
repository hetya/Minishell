/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:36:15 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/16 15:30:52 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * check if the number can be store in an int
*/
static int	is_int(char **ptr)
{
	char	*int_max;
	char	*int_min;
	size_t	i;

	i = 0;
	int_max = "2147483647";
	int_min = "-2147483648";
	while (ptr[i] != NULL)
	{
		if (ft_strlen(ptr[i]) == 10)
			if (ft_strncmp(int_max, ptr[i], ft_strlen(ptr[i])) < 0)
				return (-1);
		if (ft_strlen(ptr[i]) == 11)
			if (ft_strncmp(int_min, ptr[i], ft_strlen(ptr[i])) < 0)
				return (-1);
		if (ft_strlen(ptr[i]) > 11)
			return (-1);
		i++;
	}
	return (0);
}

/**
 * builtin : exit
 * exit the current process with the error number given in parameter
 * if the parameter isn't numeric or that there is too many parameter
 * the function will raised ans error
*/
void	shell_exit(char **ptr)
{
	int	return_value;

	if (ptr == NULL || ptr[0] == NULL)
		exit(g_return_value);
	if (*ptr[0] == '-')
		exit(112);
	if (ft_str_is_numeric(ptr[0]) == -1)
	{
		g_return_value = 128;
		ft_putendl_fd("exit\n", 2);
		exit_builtin("exit", NULL, "numeric argument required", 255);
		exit(g_return_value);
	}
	if (split_len(ptr) > 1)
	{
		g_return_value = 128;
		ft_putendl_fd("exit\n", 2);
		return (exit_builtin("exit", NULL, "too many arguments", 1));
	}
	if (is_int(&ptr[0]) == -1)
		exit(255);
	return_value = ft_atoi(ptr[0]);
	if (return_value > 255)
		return_value = return_value % 256;
	exit(return_value);
}

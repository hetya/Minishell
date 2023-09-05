/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:11:23 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/07 15:11:25 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * check if the cmd is a builtin
*/
int	check_builtin(char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "cd") == 0
		|| ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "export") == 0
		|| ft_strcmp(cmd[0], "unset") == 0 || ft_strcmp(cmd[0], "env") == 0
		|| ft_strcmp(cmd[0], "exit") == 0)
		return (1);
	return (0);
}

/**
 * execute the builtin function
*/
void	exec_builtin(t_shell *shell, char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		echo(++cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		cd (shell, cmd[1]);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd[0], "export") == 0)
		export(shell, ++cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		unset(shell, ++cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
		env(shell);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		shell_exit(++cmd);
}

/**
 * this function is called at the exit of a builtin and assign the exit_value
 * of the builtin in g_return_value
 * if there is any error it will write the error in the STDERR
*/
void	exit_builtin(char *cmd, char *arg, char *error, int exit_value)
{
	if (cmd != NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg != NULL)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error)
		ft_putendl_fd(error, 2);
	g_return_value = exit_value;
}

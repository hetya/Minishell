/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:32:57 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/16 16:13:36 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * this function will execute command
*/
static void	child(t_shell *shell, int *fd)
{
	char	*path_cmd;

	child_fd_redirect(shell, fd);
	if (check_builtin(shell->cmd->cmd))
	{
		exec_builtin(shell, shell->cmd->cmd);
		exit(0);
	}
	path_cmd = search_cmd_path(shell, shell->cmd->cmd[0]);
	execve(path_cmd, shell->cmd->cmd, shell->env);
	ft_gcfree (path_cmd);
	exit(127);
}

/**
 * this function wait until and then store the return value of the
 * command in g_return_value
*/
static void	parent(t_shell *shell)
{
	int		res;
	pid_t	a;

	res = 0;
	redirect_handler("IGN", SIGINT);
	if (shell->cmd->nextsep != 1)
	{
		a = 1;
		while (a > 0)
			a = wait(&res);
		if (res == 2)
			g_return_value = 130;
	}
	if (!g_return_value)
		g_return_value = res / 256;
	if (!shell->last_cmd)
		shell->last_cmd = res / 256;
	shell->last_cmd = res / 256;
}

/**
 * this function create a fork and call the function that will execute the
 * command if it is in the the child process
*/
void	exec_commands(t_shell *shell)
{
	pid_t	pid;
	int		fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (shell->cmd->nextsep == 1)
		if (pipe(fd) == -1)
			perror("pipe");
	pid = fork();
	if (check_pid(shell, pid, fd) == -1)
		return ;
	else if (!pid)
		child(shell, &fd[0]);
	else
	{
		close_fd(&shell->cmd->outfile);
		close_fd(&shell->cmd->infile);
		if (shell->cmd->nextsep == 1)
			close_fd(&fd[1]);
		if (shell->nextincmd >= 0)
			close_fd(&shell->nextincmd);
		if (shell->cmd->nextsep == 1)
			shell->nextincmd = fd[0];
		parent(shell);
	}
}

void	septester(t_shell *shell)
{
	if (shell->cmd->cmd && (shell->cmd->sep == 0 || (shell->cmd->sep == 2
				&& shell->last_cmd > 0) || (shell->cmd->sep == 3
				&& shell->last_cmd == 0)) && shell->cmd->nextsep != 1
		&& shell->cmd->outfile == -1 && check_builtin(shell->cmd->cmd))
	{
		g_return_value = 0;
		exec_builtin(shell, shell->cmd->cmd);
		shell->last_cmd = g_return_value;
	}
	else if (shell->cmd->cmd && (shell->cmd->sep == 0 || (shell->cmd->sep == 1
				&& shell->last_cmd == 0) || (shell->cmd->sep == 2
				&& shell->last_cmd > 0) || (shell->cmd->sep == 3
				&& shell->last_cmd == 0)))
		exec_commands(shell);
	else
	{
		if (shell->cmd->cmd)
			shell->cmd->status = -1;
		else
			shell->last_cmd = 0;
		if (shell->cmd->enterbrack)
			shell->pass = shell->inbrack;
	}
}

/**
 * this function is call for each command and it will look if the command
 * must be execute if it must it will call the exec_one_command if
 * it is a builtin else the exec_commands function will be call
*/
int	execution(t_shell *shell)
{
	redirect_handler("FORK", SIGINT);
	redirect_handler("EXC", SIGQUIT);
	if (shell->cmd->enterbrack)
		shell->inbrack += shell->cmd->enterbrack;
	if (shell->cmd != NULL && !shell->pass && shell->cmd->status >= 0)
		septester(shell);
	else if (shell->cmd->status == -1)
	{
		shell->last_cmd = 0;
		g_return_value = 1;
	}
	if (shell->cmd->exitbrack)
	{
		if (shell->pass == shell->inbrack)
			shell->pass = 0;
		shell->inbrack -= shell->cmd->exitbrack;
	}
	redirect_handler("MAIN", SIGINT);
	redirect_handler("IGN", SIGQUIT);
	return (0);
}

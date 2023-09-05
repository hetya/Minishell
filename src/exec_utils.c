/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:11:57 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/16 13:28:49 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_cmd_path(t_shell *shell, char *cmd)
{
	char	*cmd_path;
	char	**env_path;
	int		i;

	if (access(cmd, F_OK) != -1)
		return (cmd);
	if (index_search_in_env(shell->env, "PATH") == -1)
	{
		exit_builtin(NULL, cmd, "No such file or directory", 127);
		return (NULL);
	}
	env_path = ft_split(search_in_env(shell->env, "PATH"), ':');
	i = -1;
	while (env_path[++i])
	{
		cmd_path = ft_strjoin_ptr(ft_strjoin(env_path[i], "/"), cmd);
		if (!cmd_path)
			perror("Cmd Path");
		if (access(cmd_path, F_OK) != -1)
			return (cmd_path);
		ft_gcfree(cmd_path);
	}
	exit_builtin(NULL, cmd, "command not found", 127);
	return (NULL);
}

/**
 * Part at the start of the child who redirect all fd and close corresponding 
 * opened fd
 */
void	child_fd_redirect(t_shell *shell, int *fd)
{
	if (shell->cmd->infile != -1)
	{
		if (dup2(shell->cmd->infile, 0) == -1)
			perror("Dup Infile");
		close(shell->cmd->infile);
		close_fd(&shell->nextincmd);
	}
	else if (shell->nextincmd > 0)
	{
		if (dup2(shell->nextincmd, 0) == -1)
			perror("Dup Infile");
		close_fd(&shell->nextincmd);
	}
	if (shell->cmd->outfile != -1)
	{
		if (dup2(shell->cmd->outfile, 1) == -1)
			perror("Dup Pipe Fd In Outfile");
		close(shell->cmd->outfile);
	}
	else if (shell->cmd->nextsep == 1)
		if (dup2(fd[1], 1) == -1)
			perror("Dup Pipe Fd In Outfile");
	close_fd(&fd[1]);
	close_fd(&fd[0]);
}

/**
 * check if the fd is a postive number an close it if it is
*/
void	close_fd(int *fd)
{
	if (*fd >= 0)
	{
		if (close(*fd) != 0)
			perror("Close file descriptor");
	}
	*fd = -1;
}

int	check_pid(t_shell *shell, pid_t	pid, int *fd)
{
	int		res;
	pid_t	a;

	if (pid == -1)
	{
		perror("fork");
		shell->last_cmd = 1;
		close_fd(&shell->cmd->outfile);
		close_fd(&shell->cmd->infile);
		close_fd(&fd[1]);
		close_fd(&fd[0]);
		close_fd(&shell->nextincmd);
		a = 1;
		while (a > 0)
			a = wait(&res);
		return (-1);
	}
	return (0);
}

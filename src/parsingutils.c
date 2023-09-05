/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:47:06 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/16 16:24:52 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Test *totest and *(totest + 1) and :
 * 		-case "|" return 1
 * 		-case "||" return 2
 * 		-case "&&" return 3
 * 		-else return 0;
 */
int	ft_issep(char	*totest)
{
	if (!totest)
		return (0);
	if (*totest == '|' && *(totest + 1) == '|')
		return (2);
	else if (*totest == '&' && *(totest + 1) == '&')
		return (3);
	else if (*totest == '|')
		return (1);
	return (0);
}

/**
 * Remove char c from str and return the malloced result
 */
char	*ft_strdelchar(char *str, char c)
{
	char	*res;
	int		i;
	int		size;

	i = -1;
	size = strlen(str);
	while (str && str[++i])
		if (str[i] == c)
			size--;
	res = ft_gcalloc(sizeof(char), size + 1);
	i = -1;
	size = 0;
	while (str && str[++i])
		if (str[i] != c)
			res[size++] = str[i];
	return (res);
}

void	heredoc_child(int res[2], char *limiter, t_shell *shell)
{
	char	*temp;
	char	*tempe;
	int		d;

	redirect_handler("FORK", SIGINT);
	while (1)
	{
		tempe = readline(GREEN"> "END);
		temp = ft_strdup(tempe);
		free(tempe);
		if (!temp || !ft_strcmp(limiter, temp))
			break ;
		d = 0;
		while (*temp)
		{
			if (*temp == '$')
				get_env_var(&temp, &d, shell, 1);
			temp++;
			d++;
		}
		temp -= d;
		ft_putstr_fd(temp, res[1]);
		ft_putstr_fd("\n", res[1]);
	}
	exit(0);
}

/**
 * Do a here_doc limited by "limiter"
 * and return each line in a char **
 */
int	ft_heredoc(char	*limiter, t_shell *shell)
{
	int					res[2];
	pid_t				pid;

	redirect_handler("IGN", SIGINT);
	pipe(res);
	pid = fork();
	if (!pid)
		heredoc_child(res, limiter, shell);
	waitpid(-1, &pid, 0);
	redirect_handler("MAIN", SIGINT);
	if (pid)
	{
		g_return_value = 1;
		return (-1);
	}
	close(res[1]);
	wait(NULL);
	return (res[0]);
}

/**
 * Open with conditionnal fd:
 * 					-if 0: reading fd 
 * 						if lastfd close lastfd
 * 						test access exist
 * 						test access reading
 * 						try open and return associated fd
 * 					- if 1: writing fd
 * 						if lastfd close lastfd
 * 						test access writing
 * 						if append O_APPEND
 * 						else O_TRUNC
 * 						try open and return associated fd
 */
int	ft_openfile(char *file, int fd, t_bool append, int *lastfd)
{
	if (*lastfd != 0)
		close(*lastfd);
	if (fd == 0)
	{
		if (*lastfd == -2)
			return (-2);
		if (access(file, F_OK) == -1 || access(file, R_OK) == -1)
		{
			g_return_value = 1;
			perror(ft_strjoin("Minishell: ", file));
			*lastfd = -2;
			return (-2);
		}
	}
	else if (!access(file, F_OK) && access(file, W_OK) == -1)
		return ((int)ft_perror(ft_strjoin("Minishell: ", file)) - 1);
	if (fd == 1 && append == 1)
		*lastfd = open(file, O_WRONLY | O_CREAT | O_APPEND);
	else if (fd == 1)
		*lastfd = open(file, O_WRONLY | O_CREAT | O_TRUNC);
	else
		*lastfd = open(file, O_RDONLY);
	if (*lastfd == -1)
		return (-1);
	return (0);
}

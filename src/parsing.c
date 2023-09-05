/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:39:24 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/16 16:13:58 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Add char * toadd to res->cmd , malloc it and protect it 
 */
int	ft_addtocmd(t_cmddata	*res, char	*toadd)
{
	int		i;
	char	**buff;

	i = 0;
	if (res->cmd == NULL)
	{
		res->cmd = ft_gcalloc(sizeof(char *), 2);
		res->cmd[0] = toadd;
		return (0);
	}
	while (res->cmd[i])
		i++;
	buff = res->cmd;
	res->cmd = ft_gcalloc(sizeof(char *), i + 2);
	i = -1;
	while (buff[++i])
		res->cmd[i] = buff[i];
	res->cmd[i++] = toadd;
	res->cmd[i] = NULL;
	return (0);
}

void	ft_datakey(char *word, t_shell *shell, t_cmddata *res, char **line)
{
	if (!ft_strncmp("<<", word, 3))
	{
		ft_getword(res, line, &word, shell);
		close_fd(&res->infile);
		res->infile = ft_heredoc(word, shell);
		if (res->infile == -1)
			res->status = -2;
	}
	else if (!ft_strncmp("<", word, 2) && ft_getword(res, line, &word, shell))
		res->status = ft_openfile(word, 0, 0, &res->infile);
	else if (!ft_strncmp(">", word, 2) && ft_getword(res, line, &word, shell))
		res->status = ft_openfile(word, 1, 0, &res->outfile);
	else if (!ft_strncmp(">>", word, 2))
	{
		ft_getword(res, line, &word, shell);
		res->status = ft_openfile(
				word, 1, 1, &res->outfile);
	}
	else if (ft_strchr(word, '*'))
		ft_wildcard(res, word);
	else
		ft_addtocmd(res, word);
}

void	*ft_perror(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (NULL);
}

/**
 * Creat and return a t_cmddata from data between start of line
 * and first occurence of separtor
 */
t_cmddata	*ft_todata(char	**line, t_shell *shell, int wordnb)
{
	t_cmddata	*res;
	char		*word;

	word = NULL;
	res = ft_gcalloc(sizeof(t_cmddata), 1);
	wordnb = 1 + res->infile-- + res->outfile--;
	ft_getword(res, line, &word, shell);
	if (*word == '\0')
		return (NULL);
	if (shell->cmd && shell->cmd->nextsep)
		res->sep = shell->cmd->nextsep;
	if (ft_issep(word))
		return (ft_perror("syntax error"));
	ft_datakey(word, shell, res, line);
	while (ft_getword(res, line, &word, shell)
		&& ((!ft_issep(word) && shell->count < 1) || shell->count > 0))
		ft_datakey(word, shell, res, line);
	res->nextsep = ft_issep(word);
	return (res);
}

t_cmddata	*parsing(char *line, t_shell *shell)
{
	t_cmddata	*result;

	result = ft_gcalloc(sizeof(t_cmddata), 1);
	if (preparsing(ft_strdup(line), shell, result) == -1)
		return (NULL);
	shell->count = 0;
	if (!line || *line == '\0')
		return (NULL);
	while (1)
	{
		result = ft_gcalloc(sizeof(t_cmddata *), 1);
		result = ft_todata(&line, shell, 0);
		if (!result || result->status == -2)
			return (NULL);
		shell->cmd = result;
		execution(shell);
	}
	return (result);
}

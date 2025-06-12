/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hetya       <hetya@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:39:11 by hetya             #+#    #+#             */
/*   Updated: 2022/05/16 14:40:26 by hetya            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_return_value;

int	checkline(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t')
			return (1);
		line++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell				shell;
	char				*line;

	g_return_value = 0;
	struct_initialisation(&shell, envp, argc, argv);
	redirect_handler("MAIN", SIGINT);
	redirect_handler("IGN", SIGQUIT);
	while (1)
	{
		line = readline(BOLD CYAN"Finishell "END GREEN"> "END);
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (checkline(line))
		{
			add_history(line);
			parsing(line, &shell);
			free(line);
		}
	}
	ft_gcclear();
	return (g_return_value);
}

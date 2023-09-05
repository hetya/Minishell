/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hetya                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:38:39 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/14 16:27:35 by hetya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	main_sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_return_value = 1;
		write (0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		return ;
	}
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		return ;
	}
}

static void	fork_handler(int signo)
{
	if (signo == SIGINT)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		g_return_value = 130;
		exit(g_return_value);
		return ;
	}
	if (signo == SIGQUIT)
	{
		write (1, "Quit: 3\n", 8);
		rl_on_new_line();
		g_return_value = 131;
		return ;
	}
}

/**
 * Redirect signal sig to handler handler :
 * 					- IGN for ignore
 * 					- FORK for exit handlerr
 * 					- MAIN for redisplay
 */
void	redirect_handler(char *handler, int sig)
{
	struct sigaction	psa;

	if (!ft_strcmp(handler, "IGN"))
		psa.sa_handler = SIG_IGN;
	else if (!ft_strcmp(handler, "FORK"))
		psa.sa_handler = fork_handler;
	else if (!ft_strcmp(handler, "MAIN"))
		psa.sa_handler = main_sig_handler;
	sigaction(sig, &psa, NULL);
}

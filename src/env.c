/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:11:53 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/07 15:11:54 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * builtin : env
 * display the environment
*/
void	env(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->env[++i])
		if (ft_strchr(shell->env[i], '=') != NULL)
			ft_putendl_fd(shell->env[i], 1);
	return (exit_builtin(NULL, NULL, NULL, 0));
}

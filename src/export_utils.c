/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:37:51 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/07 15:37:56 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * initialized the export enviroment and sort it in alphabetical order
*/
char	**initialized_export(t_shell *shell)
{
	char	**export_env;
	char	*swap;
	int		i;
	int		j;

	i = 0;
	export_env = create_env(shell->env);
	j = split_len(export_env) - 1;
	while (i < j)
	{
		if (ft_strcmp(export_env[i], export_env[i + 1]) > 0)
		{
			swap = export_env[i + 1];
			export_env[i + 1] = export_env[i];
			export_env[i] = swap;
			i = -1;
		}
		++i;
	}
	return (export_env);
}

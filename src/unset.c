/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:34:53 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/07 16:34:54 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_variable_name(char *name)
{
	int	i;

	if (ft_str_is_numeric(name) != -1)
	{
		exit_builtin("unset", name, "not a valid identifier", 1);
		return (-1);
	}
	i = -1;
	while (name[++i])
	{
		if ((name[i] < 'A' || name[i] > 'Z')
			&& (name[i] < 'a' || name[i] > 'z')
			&& (name[i] < '0' || name[i] > '9') && name[i] != '_')
		{
			exit_builtin("unset", name, "not a valid identifier", 1);
			return (-1);
		}
	}
	return (0);
}

/**
 * free all the wanted variable
*/
static int	free_ptr(t_shell *shell, char **search)
{
	int		deleted;
	int		index;
	int		i;

	i = -1;
	deleted = 0;
	while (search[++i])
	{
		if (check_variable_name(search[i]) == -1)
			return (-1);
		index = index_search_in_env(shell->env, search[i]);
		if (index >= 0)
		{
			shell->env[index][0] = -1;
			deleted++;
		}
		else
			g_return_value = 1;
	}
	return (deleted);
}

/**
 * builtin : unset
 * this fuction unset all the environment variables given in search
*/
void	unset(t_shell *shell, char **search)
{
	char	**trunc_env;
	int		len_env;
	int		nb_variable;
	int		i;
	int		j;

	len_env = split_len(shell->env);
	nb_variable = free_ptr(shell, search);
	if (nb_variable == -1)
		return (exit_builtin(NULL, NULL, NULL, 1));
	if (!nb_variable)
		return (exit_builtin(NULL, NULL, NULL, 0));
	trunc_env = ft_gcalloc(sizeof(char *), ((len_env - nb_variable) + 1));
	i = -1;
	j = -1;
	while (++i < len_env)
	{
		if (shell->env[i][0] != -1)
			trunc_env[++j] = shell->env[i];
		else
			ft_gcfree(shell->env[i]);
	}
	ft_gcfree(shell->env);
	shell->env = trunc_env;
	return (exit_builtin(NULL, NULL, NULL, 0));
}

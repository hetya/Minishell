/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:11:36 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/07 15:11:37 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * builtin : cd
 * browse folders
 * can access to all the folder in the curennt file and
 * handel the -, ~ and NULL arg
*/
void	cd(t_shell *shell, char *dir)
{
	char	*new_dir;

	if (dir == NULL || ft_strcmp(dir, "~") == 0)
	{
		dir = search_in_env(shell->env, "HOME");
		if (dir == NULL)
			return (exit_builtin("cd", NULL, "HOME not set", 1));
	}
	else if (ft_strcmp(dir, "-") == 0)
	{
		dir = search_in_env(shell->env, "OLDPWD");
		if (dir == NULL)
			return (exit_builtin("cd", NULL, "OLDPWD not set", 1));
	}
	if (chdir(dir) == -1)
		return (exit_builtin("cd", dir, "no such file or directory", 1));
	replace_env(shell, "OLDPWD", search_in_env(shell->env, "PWD"));
	new_dir = NULL;
	new_dir = getcwd(new_dir, 0);
	if (new_dir == NULL)
		return (exit_builtin("cd", NULL, "error path", 1));
	replace_env(shell, "PWD", new_dir);
	free(new_dir);
	return (exit_builtin(NULL, NULL, NULL, 0));
}

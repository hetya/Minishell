/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_initialisation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hetya                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:33:54 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/10 16:02:10 by hetya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pwd_update(t_shell *shell)
{
	char	*pwd_path;
	char	*buf;
	char	**tmp;

	tmp = ft_split("OLDPWD", '.');
	unset(shell, (char **)tmp);
	if (index_search_in_env(shell->env, "OLDPWD") < 0)
		env_add(shell, "OLDPWD");
	pwd_path = search_in_env(shell->env, "PWD");
	if (pwd_path == NULL)
	{
		buf = NULL;
		buf = getcwd(buf, 0);
		if (buf == NULL)
		{
			perror("Env Initialization");
			return (-1);
		}
		replace_env(shell, "PWD", buf);
		free(buf);
	}
	return (0);
}

/**
 * intialized the shell structure and the environment
*/
int	struct_initialisation(t_shell *shell, char **envp, int c, void *v)
{
	char	*shlvl;
	int		shell_level;
	char	*replace;

	(void)c;
	(void)v;
	shell->last_cmd = 1;
	shell->env = create_env(envp);
	shlvl = search_in_env(shell->env, "SHLVL");
	shell->nextincmd = -1;
	if (shlvl == NULL)
		env_add(shell, "SHLVL=1");
	else
	{
		shell_level = ft_atoi(shlvl) + 1;
		replace = ft_itoa(shell_level);
		replace_env(shell, "SHLVL", replace);
		ft_gcfree(replace);
	}
	replace_env(shell, "SHELL", "Minishell");
	return (pwd_update(shell));
}

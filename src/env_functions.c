/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:11:49 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/07 15:11:50 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * create a copy of the environment using the pre-existing
 * envirinment given in parameter
 * return the new environment
*/
char	**create_env(char **envp)
{
	char	**env;
	int		i;

	env = ft_gcalloc(sizeof(char *), split_len(envp) + 1);
	i = -1;
	while (envp[++i])
		env[i] = ft_strdup(envp[i]);
	return (env);
}

/**
 * search a variable in environment using the name of the variable
 * given in parameter
 * if the variable is not present in the environment it will return -1 otherwise
 * the function will return the index value of the varible
*/
int	index_search_in_env(char **env, char *name)
{
	char	*search;
	int		i;

	i = -1;
	if (ft_strchr(name, '='))
		return (-1);
	search = ft_strjoin(name, "=");
	while (env[++i])
	{
		if (ft_strncmp(env[i], search, ft_strlen(search)) == 0
			|| ft_strcmp(env[i], name) == 0)
			return (i);
	}
	ft_gcfree(search);
	return (-1);
}

/**
 * search a variable in environment using the index_search_in_env function
 * and return it's value
 * if the variable is not present in the environment it will return NULL
*/
char	*search_in_env(char **env, char *search)
{
	int	index;

	index = index_search_in_env(env, search);
	if (index == -1 || ft_strlen(env[index]) == ft_strlen(search))
		return (NULL);
	else
		return (env[index] + (ft_strlen(search) + 1));
}

/**
 * add an environment variable
 * who is contained in str
*/
void	env_add(t_shell *shell, char *str)
{
	char	**new_env;
	int		i;

	i = -1;
	new_env = NULL;
	new_env = ft_gcalloc(sizeof(char *), split_len(shell->env) + 1 + 1);
	while (shell->env[++i])
		new_env[i] = shell->env[i];
	new_env[i] = ft_strdup(str);
	ft_gcfree(shell->env);
	shell->env = NULL;
	shell->env = new_env;
}

/**
 * replace a environment variable by searching the name and replace the value
 * of the environment variable with the str replace
 * if variable is not present in environment the replpace function will add it
*/
void	replace_env(t_shell *shell, char *name, char *replace)
{
	char	*ptr;
	int		index;

	ptr = ft_strjoin(name, "=");
	ptr = ft_strjoin_ptr(ptr, replace);
	index = index_search_in_env(shell->env, name);
	if (index == -1)
	{
		env_add(shell, ptr);
		ft_gcfree(ptr);
	}
	else
	{
		ft_gcfree(shell->env[index]);
		shell->env[index] = ptr;
	}
}

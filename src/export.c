/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:38:02 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/16 15:35:14 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * print the envrionment variable given in paramter unless it is the _= variable
*/
static void	print_variable(char *export_varaible, int sep_index)
{
	char	*key;
	char	*value;

	if (ft_strncmp(export_varaible, "_=", 2) != 0)
	{
		if (sep_index > 0)
		{
			key = ft_substr(export_varaible, 0, sep_index);
			value = ft_strdup(&export_varaible[++sep_index]);
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(value, 1);
			ft_putstr_fd("\"\n", 1);
			ft_gcfree(key);
			ft_gcfree(value);
		}
		else
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(export_varaible, 1);
			ft_putstr_fd("\n", 1);
		}
	}
}

/**
 * browse the char * array and call the function to print all the variable
*/
static void	print(t_shell *shell)
{
	char	**export_env;
	char	*variable_value;
	int		i;
	int		sep_index;

	export_env = initialized_export(shell);
	i = -1;
	while (export_env[++i])
	{
		variable_value = ft_strchr(export_env[i], '=');
		if (variable_value)
			sep_index = ft_strchr(export_env[i], '=') - export_env[i];
		else
			sep_index = -1;
		print_variable(export_env[i], sep_index);
	}
	free_split(export_env);
}

/**
 * adding the variable to environment handel the = and the += operator
 * if the variable already exist the value of the variable will be replace if
 * the = operator is used
*/
static void	add_variable(t_shell *shell, char **ptr, int i, int j)
{
	char	*key;
	char	*join_value;

	key = ft_substr(ptr[i], 0, j);
	if (ptr[i][j] == '+' && ptr[i][j + 1] == '=')
	{
		join_value = ft_strjoin(search_in_env(shell->env, key),
				&ptr[i][j + 2]);
		replace_env(shell, key, join_value);
		ft_gcfree(join_value);
	}
	else if (ptr[i][j] == '=')
		replace_env(shell, key, &ptr[i][j + 1]);
	else if (ptr[i][j] == '\0')
	{
		if (index_search_in_env(shell->env, key) == -1)
			env_add(shell, key);
	}
	else
	{
		ft_gcfree(key);
		return (exit_builtin("export", ptr[i],
				"not a valid identifier", 1));
	}
	ft_gcfree(key);
}

/**
 * check if the variable name is valid and if it is call
 * the add variable function
*/
static void	export_variable(t_shell *shell, char **ptr)
{
	int		i;
	int		j;

	i = -1;
	while (ptr[++i])
	{
		if (ft_str_is_numeric(ptr[i]) != -1 || ptr[i][0] == '='
				|| ft_isdigit(ptr[i][0]))
			return (exit_builtin("export", ptr[i],
					"not a valid identifier", 1));
		if (ft_strcmp(ptr[i], "_") == 0 || ft_strcmp(ptr[i], "_=") == 0)
			return (exit_builtin(NULL, NULL, NULL, 0));
		j = 0;
		while (((ptr[i][j] >= 'A' && ptr[i][j] <= 'Z') ||
			(ptr[i][j] >= 'a' && ptr[i][j] <= 'z') ||
			(ptr[i][j] >= '0' && ptr[i][j] <= '9') || ptr[i][j] == '_'))
			j++;
		add_variable(shell, ptr, i, j);
	}
}

/**
 * builtin : export
 * print the export environmnent
 * or add a variable to it
*/
void	export(t_shell *shell, char **ptr)
{
	if (ptr[0] == NULL)
		print(shell);
	else
		return (export_variable(shell, ptr));
	return (exit_builtin(NULL, NULL, NULL, 0));
}

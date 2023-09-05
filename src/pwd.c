/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:47:15 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/07 15:47:16 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * builtin : pwd
 * write the current pwd in STDIN
*/
void	pwd(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (buf == NULL)
		return (exit_builtin("pwd", NULL, "error path", 1));
	ft_putendl_fd(buf, 1);
	free(buf);
	return (exit_builtin(NULL, NULL, NULL, 0));
}

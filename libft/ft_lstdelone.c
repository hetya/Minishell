/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:44:29 by hetya             #+#    #+#             */
/*   Updated: 2022/03/04 16:26:03 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * clear the link passing in parameter using (del function to delete the content)
 * and free the all of the link
*/
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst->content);
		ft_gcfree(lst);
	}
}

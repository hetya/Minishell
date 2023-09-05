/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hetya                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 01:34:53 by hetya             #+#    #+#             */
/*   Updated: 2022/04/11 19:55:27 by hetya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * create a new link element with malloc
*/
static t_list	*gc_lstnew(void *content)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

/**
 * check if the linked list is already create if not create it ans store it
 * in a static variable
 * return the linked list pointer
*/
t_list	**gc_give_ptr(void)
{
	static t_list	*gc = NULL;

	if (!gc)
	{
		gc = gc_lstnew(NULL);
		if (!gc)
			exit (EXIT_FAILURE);
	}
	return (&gc);
}

/**
 * free all the gc list
*/
void	ft_gcclear(void)
{
	t_list	**gc;
	t_list	*tmp;
	t_list	*tmp2;

	gc = gc_give_ptr();
	tmp = *gc;
	while (tmp != NULL)
	{
		tmp2 = tmp->next;
		if (tmp)
		{
			free(tmp->content);
			tmp->content = NULL;
			free(tmp);
		}
		tmp = tmp2;
	}
	*gc = NULL;
}

/**
 * take the size of the element that you want malloc. Malloc it and store it
 * in a list of pointer. Call the function gc_give_ptr to have the linked list
 * return the malloc ptr
*/
void	*ft_gcalloc(size_t size, size_t count)
{
	t_list	*tmp;
	t_list	**gc;
	void	*ptr;

	gc = gc_give_ptr();
	ptr = NULL;
	tmp = NULL;
	ptr = (void *)calloc(size, count);
	if (!ptr)
		exit(EXIT_FAILURE);
	tmp = gc_lstnew((void *)ptr);
	if (!tmp)
	{
		free(tmp);
		ft_gcclear();
		exit(EXIT_FAILURE);
	}
	ft_lstadd_back(gc, tmp);
	return (ptr);
}

void	ft_gcfree(void *ptr)
{
	t_list	**gc;
	t_list	*gc_list;
	t_list	*prev;
	t_list	*tmp;

	gc = gc_give_ptr();
	gc_list = *gc;
	prev = NULL;
	while (gc_list)
	{
		if (ptr == gc_list->content)
		{
			tmp = gc_list->next;
			free(ptr);
			if (prev)
				prev->next = tmp;
			else
				*gc = tmp;
			free(gc_list);
			return ;
		}
		prev = gc_list;
		gc_list = gc_list->next;
	}
	free(ptr);
}

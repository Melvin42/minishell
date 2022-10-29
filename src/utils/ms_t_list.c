/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_t_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 18:56:50 by melperri          #+#    #+#             */
/*   Updated: 2021/10/07 10:05:55 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_list	*ms_lstnew(void *data)
{
	t_list	*ret;

	ret = NULL;
	ret = malloc(sizeof(t_list));
	if (!ret)
		return (NULL);
	ret->data = data;
	ret->prev = NULL;
	ret->next = NULL;
	return (ret);
}

void	ms_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (!alst)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	last = ms_lstlast(*alst);
	last->next = new;
}

void	ms_lstadd_front(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
	(*alst)->next->prev = new;
}

void	ms_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*previous;

	previous = NULL;
	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		previous = *lst;
		*lst = (*lst)->next;
		ms_lstdelone(previous, del);
	}
}

void	ms_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst)
	{
		del(lst->data);
		lst->data = NULL;
		free(lst);
		lst = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_t_list_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 17:55:13 by melperri          #+#    #+#             */
/*   Updated: 2021/09/09 16:51:18 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_list	*ms_lstnew_cmd(void *data)
{
	t_list	*ret;

	ret = NULL;
	ret = malloc(sizeof(t_list));
	if (!ret)
		return (NULL);
	ret->data = data;
	ret->next = NULL;
	return (ret);
}

void	ms_lstadd_back_cmd(t_list **alst, t_list *new)
{
	if (alst && new)
	{
		if (*alst == NULL)
			*alst = new;
		else
			ms_lstlast_cmd(*alst)->next = new;
	}
}

void	ms_lstadd_front_cmd(t_list **alst, t_list *new)
{
	if (alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
}

void	ms_lstclear_cmd(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		ms_lstdelone_cmd(*lst, del);
		*lst = tmp;
	}
}

void	ms_lstdelone_cmd(t_list *lst, void (*del)(void*))
{
	if (lst)
	{
		ms_free_split(&(((t_cmd *)lst->data)->cmd));
		del(((t_cmd *)lst->data)->red);
		del(((t_cmd *)lst->data)->prev_red);
		del(lst->data);
		del(lst);
	}
}

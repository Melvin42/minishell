/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_t_list2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 00:18:20 by csejault          #+#    #+#             */
/*   Updated: 2021/10/27 15:17:12 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ms_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst)
	{
		f(lst->data);
		lst = lst->next;
	}
}

t_list	*ms_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ms_lstsize(t_list *lst)
{
	size_t	s;

	if (!lst)
		return (0);
	s = 0;
	while (lst->next)
	{
		lst = lst->next;
		s++;
	}
	return (++s);
}

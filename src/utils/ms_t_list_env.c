/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_t_list_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:26:50 by melperri          #+#    #+#             */
/*   Updated: 2021/10/23 16:27:24 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ms_lstadd_back_env(t_m_shl *g, t_list *new)
{
	g->env_vers++;
	g->env_size++;
	if (!g->env[FRT])
	{
		g->env[FRT] = new;
		g->env[BCK] = new;
		return ;
	}
	g->env[BCK]->next = new;
	new->prev = g->env[BCK];
	g->env[BCK] = new;
}

void	ms_lstadd_front_env(t_m_shl *g, t_list *new)
{
	g->env_vers++;
	g->env_size++;
	new->next = g->env[FRT];
	g->env[FRT] = new;
	if (g->env[FRT]->next)
		g->env[FRT]->next->prev = new;
}

void	ms_lstdelone_env(t_m_shl *g, t_list **lst)
{
	if (lst && *lst)
	{
		g->env_vers++;
		g->env_size--;
		free(((t_env *)(*lst)->data)->key);
		((t_env *)(*lst)->data)->key = NULL;
		free(((t_env *)(*lst)->data)->val);
		((t_env *)(*lst)->data)->val = NULL;
		free((*lst)->data);
		(*lst)->data = NULL;
		free(*lst);
		*lst = NULL;
	}
}

void	ms_pop_one_env(t_m_shl *g, char *key_to_pop)
{
	t_list	*lst;
	t_env	*env;

	lst = g->env[FRT];
	while (lst)
	{
		env = (t_env *)lst->data;
		if (!ms_strcmp(env->key, key_to_pop))
		{
			if (lst->prev)
				lst->prev->next = lst->next;
			else
				g->env[FRT] = lst->next;
			if (lst->next)
				lst->next->prev = lst->prev;
			else
				g->env[BCK] = lst->prev;
			ms_lstdelone_env(g, &lst);
			lst = g->env[FRT];
			return ;
		}
		lst = lst->next;
	}
}

void	ms_lstclear_env(t_m_shl *g)
{
	t_list	*previous;

	previous = NULL;
	if (!g->env[FRT])
		return ;
	while (g->env[FRT])
	{
		previous = g->env[FRT];
		g->env[FRT] = g->env[FRT]->next;
		ms_lstdelone_env(g, &previous);
	}
}

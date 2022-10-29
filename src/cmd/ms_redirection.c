/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:17:02 by csejault          #+#    #+#             */
/*   Updated: 2021/10/27 15:26:07 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	ms_red_nbr_and_i_plus_one(int *red_nb, int *i)
{
	(*red_nb)++;
	(*i)++;
}

int	ms_set_redirection(t_m_shl *g)
{
	int	i;

	ms_memset((void *)&g->s_redir, 0, sizeof(g->s_redir));
	g->s_redir.out = -1;
	g->s_redir.savein = -1;
	g->s_redir.saveout = -1;
	g->s_redir.inst = ((t_cmd *)g->s_x.jobs->data)->cmd;
	g->s_redir.is_red = ((t_cmd *)g->s_x.jobs->data)->red;
	i = 0;
	while (g->s_redir.inst[i])
	{
		if (g->s_redir.is_red[i] == RED_S_L || g->s_redir.is_red[i] == RED_D_L)
			g->s_redir.max_l_red++;
		else if (g->s_redir.is_red[i] == RED_S_R
			|| g->s_redir.is_red[i] == RED_D_R)
			g->s_redir.max_r_red++;
		i++;
	}
	return (0);
}

int	ms_redirection_left(t_m_shl *g)
{
	while (g->s_redir.inst[g->s_redir.i])
	{
		if (g->s_redir.is_red[g->s_redir.i] == RED_S_L)
			ms_red_nbr_and_i_plus_one(&g->s_redir.l_red_nb, &g->s_redir.i);
		else if (g->s_redir.is_red[g->s_redir.i] == RED_D_L)
		{
			if (ms_red_double_l(g))
				return (g_errno);
		}
		g->s_redir.i++;
	}
	g->s_redir.l_red_nb = 0;
	g->s_redir.i = 0;
	while (g->s_redir.inst[g->s_redir.i])
	{
		if (g->s_redir.is_red[g->s_redir.i] == RED_D_L)
			ms_red_nbr_and_i_plus_one(&g->s_redir.l_red_nb, &g->s_redir.i);
		else if (g->s_redir.is_red[g->s_redir.i] == RED_S_L)
		{
			if (ms_red_simple_l(g))
				return (g_errno);
		}
		g->s_redir.i++;
	}
	return (0);
}

int	ms_redirection(t_m_shl *g)
{
	ms_set_redirection(g);
	if (ms_redirection_left(g))
		return (g_errno);
	g->s_redir.i = 0;
	while (g->s_redir.inst[g->s_redir.i])
	{
		if (g->s_redir.is_red[g->s_redir.i])
		{
			if (g->s_redir.is_red[g->s_redir.i] == RED_S_R)
			{
				if (ms_red_simple_r(g))
					return (g_errno = errno);
			}
			else if (g->s_redir.is_red[g->s_redir.i] == RED_D_R)
			{
				if (ms_red_double_r(g))
					return (g_errno = errno);
			}
		}
		g->s_redir.i++;
	}
	return (0);
}

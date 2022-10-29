/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirect_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:49:03 by csejault          #+#    #+#             */
/*   Updated: 2021/10/27 15:28:54 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	ms_close_out_if_not_last(t_m_shl *g)
{
	if (g->s_redir.r_red_nb < g->s_redir.max_r_red)
	{
		if (close(g->s_redir.out))
			return (g_errno = errno);
		g->s_redir.out = -1;
	}
	return (0);
}

int	ms_red_simple_l(t_m_shl *g)
{
	struct stat	sb;
	char		*path;

	g->s_redir.i++;
	g->s_redir.l_red_nb++;
	path = g->s_redir.inst[g->s_redir.i];
	if (stat(path, &sb))
		return (g_errno = -errno);
	if (g->s_redir.l_red_nb == g->s_redir.max_l_red && g->s_redir.l_red_nb > 0)
	{
		g->s_redir.input[0] = open(path, O_RDONLY, 0644);
		if (g->s_redir.input[0] < 0)
			return (g_errno = errno);
	}
	return (0);
}

int	ms_red_double_r(t_m_shl *g)
{
	char	*path;

	g->s_redir.r_red_nb++;
	g->s_redir.i++;
	path = g->s_redir.inst[g->s_redir.i];
	g->s_redir.out = open(path, O_APPEND | O_CREAT | O_RDWR, 0644);
	if (g->s_redir.out < 0)
		return (g_errno = errno);
	if (ms_close_out_if_not_last(g))
		return (g_errno = errno);
	if (g->s_redir.r_red_nb == g->s_redir.max_r_red && g->s_redir.r_red_nb > 0)
	{
		g->s_redir.saveout = dup(1);
		if (dup2(g->s_redir.out, 1) < 0)
			return (g_errno = errno);
		close(g->s_redir.out);
		g->s_redir.out = -1;
	}
	return (0);
}

int	ms_red_simple_r(t_m_shl *g)
{
	char	*path;

	g->s_redir.r_red_nb++;
	g->s_redir.i++;
	path = g->s_redir.inst[g->s_redir.i];
	g->s_redir.out = open(path, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (g->s_redir.out < 0)
		return (g_errno = errno);
	if (ms_close_out_if_not_last(g))
		return (g_errno = errno);
	if (g->s_redir.r_red_nb == g->s_redir.max_r_red && g->s_redir.r_red_nb > 0)
	{
		g->s_redir.saveout = dup(1);
		if (dup2(g->s_redir.out, 1) < 0)
			return (g_errno = errno);
		close(g->s_redir.out);
		g->s_redir.out = -1;
	}
	return (0);
}

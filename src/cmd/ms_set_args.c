/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_set_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:32:28 by csejault          #+#    #+#             */
/*   Updated: 2021/10/27 15:24:45 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	ms_args_mal(t_m_shl *g)
{
	int	i;
	int	arg_nbr;

	arg_nbr = 0;
	i = 0;
	g->s_x.args = malloc((g->s_args.len + 1) * sizeof(*g->s_x.args));
	if (!g->s_x.args)
		return (g_errno = errno);
	g->s_x.args[0] = NULL;
	while (g->s_args.inst[i])
	{
		if (!g->s_args.is_red[i]
			&& ((i > 0 && !g->s_args.is_red[i - 1]) || i == 0))
		{
			g->s_x.args[arg_nbr] = ms_strdup(g->s_args.inst[i]);
			if (!g->s_x.args[arg_nbr])
				return (g_errno = errno);
			arg_nbr++;
			g->s_x.args[arg_nbr] = NULL;
		}
		i++;
	}
	return (0);
}

int	ms_args_len(t_m_shl *g)
{
	int	i;

	i = 0;
	while (g->s_args.inst[i])
	{
		if (g->s_args.is_red[i])
			g->s_args.len -= 2;
		g->s_args.len++;
		i++;
	}
	return (0);
}

int	ms_set_args(t_m_shl *g)
{
	g->s_args.inst = ((t_cmd *)g->s_x.jobs->data)->cmd;
	g->s_args.is_red = ((t_cmd *)g->s_x.jobs->data)->red;
	g->s_args.len = 0;
	ms_args_len(g);
	if (ms_args_mal(g))
		return (g_errno);
	return (0);
}

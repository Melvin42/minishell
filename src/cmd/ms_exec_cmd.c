/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 15:17:23 by csejault          #+#    #+#             */
/*   Updated: 2021/10/20 19:08:02 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	ms_exec_cmd(t_m_shl *g)
{
	if (ms_set_path(g))
		return (g_errno);
	if (!((t_cmd *)g->pipe->data)->cmd)
		return (g_errno);
	g->s_x.jobs = g->pipe;
	if (!g->p.pipe_nbr)
	{
		if (ms_fork_cmd_w_no_pipe(g))
			return (g_errno);
	}
	else if (ms_fork_cmd_w_pipe(g))
		return (g_errno);
	ms_reset_s_exec(g);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 10:31:36 by csejault          #+#    #+#             */
/*   Updated: 2021/10/06 15:00:23 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	ms_close_all_pipe(t_m_shl *g)
{
	int	i;

	i = 0;
	while (i < g->p.pipe_nbr * 2)
		close(g->s_x.p_fd[i++]);
	return (0);
}

int	ms_create_pipe(t_m_shl *g)
{
	int	i;

	g->s_x.p_fd = malloc(sizeof(*g->s_x.p_fd) * g->p.pipe_nbr * 2);
	if (!g->s_x.p_fd)
		return (g_errno = errno);
	i = 0;
	while (i < g->p.pipe_nbr)
	{
		if (pipe(g->s_x.p_fd + i * 2))
			return (g_errno = errno);
		i++;
	}
	return (0);
}

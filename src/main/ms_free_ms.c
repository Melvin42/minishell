/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_ms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 18:21:44 by melperri          #+#    #+#             */
/*   Updated: 2021/10/27 15:22:48 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ms_g_errno(void)
{
	g_errno = errno;
	return (-1);
}

int	ms_free_ms(t_m_shl *g)
{
	ms_free((void **)&g->s_pmt.line);
	ms_lstclear_cmd(&g->pipe, free);
	ms_lstclear_env(g);
	ms_free_path(g);
	ms_free_xpt(g);
	ms_free_s_exec(g);
	ms_free_split(&g->env_ms);
	ms_free((void **)&g->s_pmt.pwd);
	rl_clear_history();
	return (0);
}

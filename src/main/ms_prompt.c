/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 15:27:41 by csejault          #+#    #+#             */
/*   Updated: 2021/10/06 17:01:46 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	ms_reload_prompt(t_m_shl *g)
{
	ms_lstclear_cmd(&g->pipe, free);
	ms_memset(&g->p, 0, sizeof(g->p));
	ms_free((void **)&g->s_pmt.pwd);
	g_errno = 0;
}

int	ms_prompt(t_m_shl *g)
{
	ms_check_sig_main();
	ms_reload_prompt(g);
	ms_free((void **)&g->s_pmt.line);
	if (ms_env_find_kval(g, "PWD"))
		g->s_pmt.pwd = ms_strjoin("\033[1m\033[32m", ms_env_find_kval(g, "PWD"));
	else
		g->s_pmt.pwd = ms_strdup("");
	if (g->s_pmt.pwd == NULL)
		return (g_errno = errno);
	g->s_pmt.pwd = ms_strj_fr_1(g->s_pmt.pwd, "\033[1m\033[31m$ \033[0m");
	if (g->s_pmt.pwd == NULL)
		return (g_errno);
	g->s_pmt.line = readline(g->s_pmt.pwd);
	if (g->s_pmt.line && *g->s_pmt.line)
		add_history(g->s_pmt.line);
	if (!g->s_pmt.line)
	{
		write(1, "exit\n", 5);
		ms_free_ms(g);
		return (-1);
	}
	return (0);
}

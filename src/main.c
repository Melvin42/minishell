/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:24:00 by csejault          #+#    #+#             */
/*   Updated: 2021/10/27 15:17:59 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_print_error_msg(char *toprint, int code)
{
	write(2, toprint, ms_strlen(toprint));
	write(2, "\n", 1);
	return (code);
}

int	ms_main_error(t_m_shl *g)
{
	ms_print_error_msg(strerror(g_errno), g_errno);
	ms_free_ms(g);
	return (g_errno);
}

int	ms_loop_prompt(t_m_shl *g)
{
	char	**cmd;

	while (1)
	{
		if (ms_prompt(g))
			return (g_errno);
		else
		{
			g->p.ret = ms_create_lst_pipe(g, g->s_pmt.line);
			if (g->p.ret == 0)
			{
				cmd = ((t_cmd *)g->pipe->data)->cmd;
				if (ms_strncmp(cmd[0], "", 1) == 0)
					continue ;
				else if (ms_exec_cmd(g))
					return (g_errno);
			}
			else if (g->p.ret == RAFTER_NB_ERROR || g->p.ret == PIPE_ERROR
				|| g->p.ret == UNCLOSE_S_QUOTE || g->p.ret == UNCLOSE_D_QUOTE)
				continue ;
			else
				return (g_errno = errno);
		}
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_m_shl	g;

	(void)ac;
	(void)av;
	ms_set_default(&g);
	if (ms_create_lst_env(&g, envp))
		return (ms_main_error(&g));
	if (ms_cp_env(&g))
		return (ms_main_error(&g));
	if (ms_loop_prompt(&g))
		return (ms_main_error(&g));
	ms_free_ms(&g);
	return (0);
}

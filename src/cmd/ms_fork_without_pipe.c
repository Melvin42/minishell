/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fork_without_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:00:06 by csejault          #+#    #+#             */
/*   Updated: 2021/10/23 14:50:04 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static int	ms_fork_cmd_w_no_pioe_fork(t_m_shl *g)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = 0;
	pid = fork();
	ms_check_sig_fork();
	if (pid < 0)
		return (g_errno = errno);
	else if (!pid)
	{
		execve(g->s_x.to_exec, g->s_x.args, g->env_ms);
		exit(EXIT_SUCCESS);
	}
	wait(&status);
	ms_set_g_exec_ret(g, status);
	return (0);
}

static int	ms_fork_cmd_w_no_pipe2(t_m_shl *g)
{
	if (g->s_x.args[0])
	{
		if (access(g->s_x.to_exec, F_OK) != 0)
		{
			write(2, g->s_x.to_exec, ms_strlen(g->s_x.to_exec));
			ms_print_error_msg(STR_BAD_CMD, BAD_CMD);
			ms_set_g_exec_ret(g, 32512);
			return (0);
		}
		if (ms_fork_cmd_w_no_pioe_fork(g))
			return (g_errno);
	}
	if (g->s_redir.input[0] > 0)
	{
		dup2(g->s_redir.savein, 0);
		ms_close_fd(&g->s_redir.input[0]);
	}
	return (0);
}

static int	ms_exec_builtin(t_m_shl *g)
{
	if ((g->s_builtin.fct[g->s_x.builtin_nbr])(g))
	{
		ms_set_g_exec_ret(g, 32512);
		return (g_errno = errno);
	}
	else if (g->exec_ret != EXIT_TO_MANY_ARGS_ERROR)
		ms_set_g_exec_ret(g, 0);
	else
		ms_set_g_exec_ret(g, 256);
	return (0);
}

int	ms_fork_cmd_w_no_pipe(t_m_shl *g)
{
	if (ms_set_s_exec(g))
		return (g_errno);
	if (ms_redirection(g))
		return (g_errno);
	if (g->s_redir.input[0] > 0)
	{
		g->s_redir.savein = dup(0);
		if (g->s_redir.savein < 0)
			return (g_errno = errno);
		if (dup2(g->s_redir.input[0], 0))
			return (g_errno = errno);
	}
	if (g->s_x.builtin_nbr >= 0)
	{
		if (ms_exec_builtin(g))
			return (g_errno);
	}
	else if (ms_fork_cmd_w_no_pipe2(g))
		return (g_errno = errno);
	if (g->s_redir.r_red_nb == g->s_redir.max_r_red && g->s_redir.r_red_nb > 0)
	{
		dup2(g->s_redir.saveout, 1);
		ms_close_fd(&g->s_redir.saveout);
	}
	return (0);
}

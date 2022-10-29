/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fork_with_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:13:00 by csejault          #+#    #+#             */
/*   Updated: 2021/10/26 17:53:10 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static int	ms_fork_child_action(t_m_shl *g)
{
	if (g->s_x.job_id)
		if (dup2(g->s_x.p_fd[((g->s_x.job_id - 1) * 2)], 0) < 0)
			exit(g_errno = errno);
	if (!(g->s_redir.r_red_nb == g->s_redir.max_r_red
			&& g->s_redir.r_red_nb > 0) && g->s_x.jobs->next)
		if (dup2(g->s_x.p_fd[g->s_x.job_id * 2 + 1], 1) < 0)
			exit(g_errno = errno);
	ms_close_fd(&g->s_redir.saveout);
	ms_close_all_pipe(g);
	if (g->s_x.args[0])
	{
		if (g->s_x.builtin_nbr >= 0)
		{
			if ((g->s_builtin.fct[g->s_x.builtin_nbr])(g))
				exit(g_errno = errno);
		}
		else if (execve(g->s_x.to_exec, g->s_x.args, g->env_ms) < 0)
			exit (g_errno = errno);
	}
	exit(EXIT_SUCCESS);
}

int	ms_exec_job(t_m_shl *g, pid_t *pid)
{
	if (ms_set_s_exec(g))
		return (g_errno);
	if (ms_redirection(g))
		return (g_errno);
	if (g->s_x.args[0]
		&& access(g->s_x.to_exec, F_OK) != 0 && g->s_x.builtin_nbr < 0)
	{
		g_errno = errno;
		write(2, g->s_x.to_exec, ms_strlen(g->s_x.to_exec));
		ms_print_error_msg(STR_BAD_CMD, BAD_CMD);
		ms_set_g_exec_ret(g, 32512);
		return (0);
	}
	(*pid) = fork();
	ms_check_sig_fork();
	if ((*pid) < 0)
		exit(EXIT_FAILURE);
	else if (!(*pid))
		ms_fork_child_action(g);
	if (g->s_redir.r_red_nb == g->s_redir.max_r_red && g->s_redir.r_red_nb > 0)
	{
		dup2(g->s_redir.saveout, 1);
		ms_close_fd(&g->s_redir.saveout);
	}
	return (0);
}

int	ms_fork_for_every_jobs(t_m_shl *g)
{
	pid_t	pid;

	pid = 0;
	while (g->s_x.jobs)
	{
		if (ms_exec_job(g, &pid))
			return (g_errno);
		g->s_x.job_id++;
		ms_free_split(&g->s_x.full_cmd);
		ms_free_split(&g->s_x.args);
		g->s_x.jobs = g->s_x.jobs->next;
	}
	return (0);
}

int	ms_fork_cmd_w_pipe(t_m_shl *g)
{
	int		status;
	int		i;

	status = 0;
	if (ms_create_pipe(g))
		return (g_errno);
	if (ms_fork_for_every_jobs(g))
		return (g_errno);
	ms_close_all_pipe(g);
	i = 0;
	while (i < g->p.pipe_nbr + 1)
	{
		wait(&status);
		if (!g_errno)
			ms_set_g_exec_ret(g, status);
		i++;
	}
	ms_free((void **)&g->s_x.p_fd);
	return (0);
}

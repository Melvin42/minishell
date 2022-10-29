/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 18:24:34 by melperri          #+#    #+#             */
/*   Updated: 2021/10/26 17:56:58 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ms_set_g_exec_ret(t_m_shl *g, int status)
{
	if (g_errno == 130 || g_errno == 131)
	{
		if (g_errno == 130)
			g->exec_ret = 130;
		else if (g_errno == 131)
			g->exec_ret = 131;
		g_errno = 0;
	}
	else
	{
		if (status > 0)
			g->exec_ret = status / 256;
		else if (status == EXIT_TO_MANY_ARGS_ERROR)
			g->exec_ret = EXIT_TO_MANY_ARGS_ERROR;
		else
			g->exec_ret = 0;
	}
}

static void	ms_sig_handler_fork(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_errno = 130;
	}
	else if (signum == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		g_errno = 131;
	}
}

static void	ms_sig_handler_main(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_errno = 130;
	}
}

int	ms_check_sig_fork(void)
{
	if (signal(SIGINT, ms_sig_handler_fork) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	else if (signal(SIGQUIT, ms_sig_handler_fork) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	return (0);
}

int	ms_check_sig_main(void)
{
	if (signal(SIGINT, ms_sig_handler_main) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	else if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	return (0);
}

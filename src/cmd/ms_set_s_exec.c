/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_set_s_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 17:36:06 by csejault          #+#    #+#             */
/*   Updated: 2021/10/07 10:09:51 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	ms_concat_cmd(t_m_shl *g, char **cmd)
{
	int	i;
	int	l_path;
	int	l_cmd;

	l_cmd = ms_strlen(cmd[0]);
	g->s_x.full_cmd = malloc(sizeof(*g->s_x.full_cmd) * (g->s_path.line + 1));
	if (!g->s_x.full_cmd)
		return (g_errno = errno);
	g->s_x.full_cmd[g->s_path.line] = NULL;
	i = 0;
	while (i < g->s_path.line)
	{
		l_path = g->s_path.len_line[i];
		g->s_x.full_cmd[i] = malloc(sizeof(**g->s_x.full_cmd)
				* (l_path + l_cmd + 2));
		if (!g->s_x.full_cmd[i])
			return (g_errno = errno);
		ms_strcat_w_len(g->s_x.full_cmd[i], (g->s_path.path)[i], 0, l_path);
		ms_strcat_w_len(g->s_x.full_cmd[i], "/", l_path, 1);
		ms_strcat_w_len(g->s_x.full_cmd[i], cmd[0], l_path + 1, l_cmd);
		i++;
		g->s_x.full_cmd[i] = NULL;
	}
	return (0);
}

int	ms_is_cmd_valid(char **full_cmd)
{
	struct stat	sb;
	int			i;

	i = -1;
	while (full_cmd[++i])
		if (stat(full_cmd[i], &sb) == 0)
			break ;
	if (full_cmd[i] == NULL)
		return (-1);
	return (i);
}

int	ms_reset_s_exec(t_m_shl *g)
{
	g->s_x.job_id = 0;
	g->s_x.builtin_nbr = -1;
	ms_free_split(&g->s_x.full_cmd);
	ms_free_split(&g->s_x.args);
	return (0);
}

int	ms_cmd_is_builtin(t_m_shl *g)
{
	int	i;

	i = 0;
	while (i < NB_BUILTIN)
	{
		if (!ms_strcmp(((t_cmd *)g->s_x.jobs->data)->cmd[0],
				g->s_builtin.name[i]))
			break ;
		i++;
	}
	if (i < NB_BUILTIN)
		return (i);
	return (-1);
}

int	ms_set_s_exec(t_m_shl *g)
{
	int	i;

	i = -1;
	g->s_x.fdin = 0;
	g->s_x.fdout = 1;
	if (ms_set_args(g))
		return (g_errno);
	g->s_x.builtin_nbr = ms_cmd_is_builtin(g);
	g->s_x.to_exec = g->s_x.args[0];
	if (g->s_x.builtin_nbr < 0 && g->s_x.args[0])
	{
		if (ms_concat_cmd(g, g->s_x.args))
			return (g_errno);
		i = ms_is_cmd_valid(g->s_x.full_cmd);
		if (i >= 0)
			g->s_x.to_exec = g->s_x.full_cmd[i];
	}
	return (0);
}

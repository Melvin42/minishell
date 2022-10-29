/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_set_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:11:18 by csejault          #+#    #+#             */
/*   Updated: 2021/10/27 15:25:21 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	ms_update_len_path(t_m_shl *g, int i)
{
	int	l_path;

	l_path = 0;
	if (g->s_path.path[i])
	{
		while (g->s_path.path[i][l_path])
			l_path++;
		if (ms_update_len_path(g, i + 1))
			return (g_errno = errno);
	}
	else if (!g->s_path.path[i])
	{
		g->s_path.line = i;
		g->s_path.len_line = malloc(sizeof(*g->s_path.len_line) * (i + 1));
		if (!g->s_path.len_line)
			return (g_errno = errno);
	}
	g->s_path.len_line[i] = l_path;
	return (0);
}

int	ms_update_nopath(t_m_shl *g)
{
	ms_free_path(g);
	g->s_path.path = malloc(sizeof(*g->s_path.path));
	if (!g->s_path.path)
		return (g_errno = errno);
	*g->s_path.path = NULL;
	if (ms_update_len_path(g, 0))
		return (g_errno);
	return (0);
}

int	ms_update_path(t_m_shl *g, t_list *env)
{
	ms_free_path(g);
	g->s_path.path_save = ms_strdup(((t_env *)env->data)->val);
	if (!g->s_path.path_save)
		return (g_errno = errno);
	g->s_path.path = ms_split(((t_env *)env->data)->val, ':');
	if (!g->s_path.path)
		return (g_errno = errno);
	if (ms_update_len_path(g, 0))
		return (g_errno);
	return (0);
}

int	ms_set_path(t_m_shl *g)
{
	t_list	*env;

	env = g->env[0];
	while (env)
	{
		if (!ms_strcmp(((t_env *)env->data)->key, "PATH"))
		{
			if (ms_strcmp(g->s_path.path_save, ((t_env *)env->data)->val))
				if (ms_update_path(g, env))
					return (g_errno);
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
		if (ms_update_nopath(g))
			return (g_errno);
	return (0);
}

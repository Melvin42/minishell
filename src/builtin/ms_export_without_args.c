/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_without_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:28:01 by melperri          #+#    #+#             */
/*   Updated: 2021/09/17 15:28:03 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ms_export_declarex(t_m_shl *g)
{
	int		i;
	char	**to_print;
	int		fd;

	fd = 1;
	i = 0;
	while (g->s_xpt.srt_env[i])
	{
		to_print = g->s_xpt.srt_env[i];
		write(fd, "declare -x ", 11);
		write(fd, to_print[KEY], ms_strlen(to_print[KEY]));
		if (to_print[VAL])
		{
			write(fd, "=\"", 2);
			write(fd, to_print[VAL], ms_strlen(to_print[VAL]));
			write(fd, "\"", 1);
		}
		write(fd, "\n", 1);
		i++;
	}
	return (0);
}

int	ms_export_create_tabs(t_m_shl *g)
{
	t_list	*lst;
	int		i;

	lst = g->env[0];
	g->s_xpt.env_vers = g->env_vers;
	g->s_xpt.srt_env = ms_calloc(sizeof(*g->s_xpt.srt_env), (g->env_size + 1));
	if (!g->s_xpt.srt_env)
		return (g_errno = errno);
	i = 0;
	while (lst)
	{
		g->s_xpt.srt_env[i] = malloc(sizeof(**g->s_xpt.srt_env) * (2 + 1));
		if (!g->s_xpt.srt_env[i])
			return (g_errno = errno);
		g->s_xpt.srt_env[i][0] = ((t_env *)lst->data)->key;
		g->s_xpt.srt_env[i][1] = ((t_env *)lst->data)->val;
		g->s_xpt.srt_env[i][2] = NULL;
		lst = lst->next;
		i++;
	}
	g->s_xpt.srt_env[i] = NULL;
	ms_export_sort_tab(g);
	return (0);
}

int	ms_export_sort_tab(t_m_shl *g)
{
	int		i;
	int		pos;
	int		final_pos;
	char	***srt_env;

	srt_env = g->s_xpt.srt_env;
	pos = 0;
	while (pos < g->env_size)
	{
		i = pos;
		final_pos = pos;
		while (i < g->env_size)
		{
			if (0 < ms_strcmp(srt_env[pos][KEY], srt_env[i][KEY]))
				final_pos++;
			i++;
		}
		if (pos != final_pos)
			ms_export_swap_tab(pos, final_pos, &srt_env);
		else
			pos++;
	}
	return (0);
}

int	ms_export_swap_tab(int src, int dest, char ****array)
{
	char	**tmp;

	tmp = (*array)[dest];
	(*array)[dest] = (*array)[src];
	(*array)[src] = tmp;
	return (0);
}

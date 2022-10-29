/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:12:34 by csejault          #+#    #+#             */
/*   Updated: 2021/10/27 15:21:05 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ms_free(void **tofree)
{
	if (*tofree)
	{
		free(*tofree);
		*tofree = NULL;
	}
	return (0);
}

int	ms_free_xpt(t_m_shl *g)
{
	int	i;

	i = 0;
	if (!g->s_xpt.srt_env)
		return (-1);
	while (g->s_xpt.srt_env[i])
	{
		free(g->s_xpt.srt_env[i]);
		g->s_xpt.srt_env[i] = NULL;
		i++;
	}
	free(g->s_xpt.srt_env);
	g->s_xpt.srt_env = NULL;
	return (0);
}

int	ms_free_path(t_m_shl *g)
{
	ms_free((void **)&g->s_path.len_line);
	ms_free((void **)&g->s_path.path_save);
	ms_free_split(&g->s_path.path);
	return (0);
}

int	ms_free_t_env(t_env *data, bool is_error)
{
	int	ret;

	if (is_error)
	{
		g_errno = errno;
		ret = errno;
	}
	else
		ret = 0;
	ms_free((void **)&data->key);
	ms_free((void **)&data->val);
	ms_free((void **)&data);
	return (ret);
}

int	ms_free_s_exec(t_m_shl *g)
{
	ms_free((void **)&g->s_x.p_fd);
	ms_free_split(&g->s_x.full_cmd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 14:13:31 by csejault          #+#    #+#             */
/*   Updated: 2021/10/23 16:30:48 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_env	*ms_create_data_env(char **cmd, int i)
{
	t_env	*data;

	data = NULL;
	data = malloc(sizeof(*data));
	if (!data)
	{
		g_errno = errno;
		return (NULL);
	}
	if (ms_split_first_limiter(cmd[i], '=', &data->key, &data->val))
	{
		g_errno = errno;
		ms_free((void **)data);
		return (NULL);
	}
	return (data);
}

void	ms_export_check_error(int error, char **cmd)
{
	if (error)
	{
		write(2, "bash: export: `", 15);
		write (2, cmd[error], ms_strlen(cmd[error]));
		write(2, "': not a valid identifier\n", 26);
	}
}

int	ms_export_with_args(t_m_shl *g, char **cmd)
{
	int		i;
	t_env	*data;
	int		error;

	error = 0;
	data = NULL;
	i = 1;
	while (cmd[i])
	{
		data = ms_create_data_env(cmd, i);
		if (!data)
			return (g_errno);
		if (!*data->key || !ms_str_is_alnum_undscr(data->key)
			|| !((ms_isalpha(data->key[0])) || data->key[0] == '_'))
		{
			ms_free_t_env(data, KO);
			if (!error)
				error = i;
		}
		else if (ms_env_update(g, data))
			return (ms_free_t_env(data, KO));
		i++;
	}
	ms_export_check_error(error, cmd);
	return (0);
}

int	ms_export(t_m_shl *g)
{
	char	**cmd;

	cmd = g->s_x.args;
	if (!cmd[1])
	{
		if (g->s_xpt.env_vers != g->env_vers)
		{
			ms_free_xpt(g);
			if (ms_export_create_tabs(g))
				return (g_errno);
		}
		ms_export_declarex(g);
	}
	else
	{
		if (ms_export_with_args(g, cmd))
			return (g_errno);
	}
	if (ms_cp_env(g) != 0)
		return (-1);
	return (0);
}	

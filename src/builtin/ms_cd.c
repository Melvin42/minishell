/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 14:14:08 by csejault          #+#    #+#             */
/*   Updated: 2021/10/27 15:18:53 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ms_cd_update_old_pwd(t_m_shl *g)
{
	t_env	*old_pwd;

	old_pwd = ms_calloc(1, sizeof(*old_pwd));
	if (!old_pwd)
		return (g_errno = errno);
	old_pwd->key = ms_strdup("OLDPWD");
	if (!old_pwd->key)
		return (ms_free_t_env(old_pwd, KO));
	old_pwd->val = ms_env_find_kval(g, "PWD");
	if (old_pwd->val)
	{
		old_pwd->val = ms_strdup(old_pwd->val);
		if (!old_pwd->val)
			return (ms_free_t_env(old_pwd, KO));
		if (ms_env_update(g, old_pwd))
			return (ms_free_t_env(old_pwd, KO));
	}
	else
		ms_free_t_env(old_pwd, OK);
	return (0);
}

int	ms_cd_update_pwd(t_m_shl *g)
{
	t_env	*data;

	data = ms_calloc(1, sizeof(*data));
	if (!data)
		return (g_errno = errno);
	data->key = ms_strdup("PWD");
	if (!data->key)
		return (ms_free_t_env(data, KO));
	data->val = getcwd(NULL, PATH_MAX);
	if (!data->val)
		return (ms_free_t_env(data, KO));
	if (ms_env_update(g, data))
		return (ms_free_t_env(data, KO));
	return (0);
}

int	ms_cd_minus(t_m_shl *g)
{
	char	*oldpwd;

	oldpwd = ms_env_find_kval(g, "OLDPWD");
	if (oldpwd)
	{
		if (chdir(oldpwd))
		{
			g_errno = errno;
			return (ms_print_error_msg(strerror(errno), KO));
		}
	}
	else
		return (ms_print_error_msg("bash: cd: OLDPWD not set", KO));
	return (0);
}

int	ms_cd(t_m_shl *g)
{
	int		len_split;
	char	*home;

	len_split = ms_len_split(g->s_x.args);
	if (len_split == 1)
	{
		home = ms_env_find_kval(g, "HOME");
		if (!home)
			return (ms_print_error_msg(STR_CD_NO_HOME_ERROR, OK));
		else if (chdir(home))
			return (ms_print_error_msg(strerror(errno), OK));
	}
	else if (!ms_strcmp("-", g->s_x.args[1]))
	{
		if (ms_cd_minus(g))
			return (g_errno);
	}
	else if (chdir(g->s_x.args[1]))
		return (ms_print_error_msg(strerror(errno), OK));
	if (ms_cd_update_old_pwd(g))
		return (g_errno);
	if (ms_cd_update_pwd(g))
		return (g_errno);
	return (0);
}

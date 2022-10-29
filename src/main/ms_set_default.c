/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_set_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:50:54 by csejault          #+#    #+#             */
/*   Updated: 2021/08/30 17:46:12 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ms_set_s_builtin(t_m_shl *g)
{
	ms_strcpy(g->s_builtin.str_echo, "echo");
	ms_strcpy(g->s_builtin.str_cd, "cd");
	ms_strcpy(g->s_builtin.str_pwd, "pwd");
	ms_strcpy(g->s_builtin.str_export, "export");
	ms_strcpy(g->s_builtin.str_unset, "unset");
	ms_strcpy(g->s_builtin.str_env, "env");
	ms_strcpy(g->s_builtin.str_exit, "exit");
	g->s_builtin.name[0] = g->s_builtin.str_echo;
	g->s_builtin.name[1] = g->s_builtin.str_cd;
	g->s_builtin.name[2] = g->s_builtin.str_pwd;
	g->s_builtin.name[3] = g->s_builtin.str_export;
	g->s_builtin.name[4] = g->s_builtin.str_unset;
	g->s_builtin.name[5] = g->s_builtin.str_env;
	g->s_builtin.name[6] = g->s_builtin.str_exit;
	g->s_builtin.fct[0] = &(ms_echo);
	g->s_builtin.fct[1] = &(ms_cd);
	g->s_builtin.fct[2] = &(ms_pwd);
	g->s_builtin.fct[3] = &(ms_export);
	g->s_builtin.fct[4] = &(ms_unset);
	g->s_builtin.fct[5] = &(ms_env);
	g->s_builtin.fct[6] = &(ms_exit);
	return (0);
}

int	ms_set_default(t_m_shl *g)
{
	g_errno = 0;
	ms_memset(g, 0, sizeof(t_m_shl));
	ms_set_s_builtin(g);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 15:06:41 by csejault          #+#    #+#             */
/*   Updated: 2021/09/08 18:40:39 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

/*		ms_exit.c */
int		ms_exit(t_m_shl *g);

/*		ms_export_without_args.c */
int		ms_export_declarex(t_m_shl *g);
int		ms_export_create_tabs(t_m_shl *g);
int		ms_export_sort_tab(t_m_shl *g);
int		ms_export_swap_tab(int src, int dest, char ****array);

/*		ms_export.c */
int		ms_export(t_m_shl *g);

/*		ms_cd.c */
int		ms_cd(t_m_shl *g);

/*		ms_echo */
int		ms_echo(t_m_shl *g);

/*		ms_env.c */
int		ms_env(t_m_shl *g);

/*		ms_pwd.c */
int		ms_pwd(t_m_shl *g);

/*		ms_unset */
int		ms_unset(t_m_shl *g);

#endif

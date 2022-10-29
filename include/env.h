/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 23:24:03 by csejault          #+#    #+#             */
/*   Updated: 2021/10/13 12:19:14 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

/*		ms_env.c */
char	*ms_env_find_kval(t_m_shl *g, char *key_to_find);
int		ms_env_print_kval(t_m_shl *g, char *key_to_find);
int		ms_env_update(t_m_shl *g, t_env *data);
int		ms_create_lst_env(t_m_shl *g, char **envp);

/*		ms_cp_env.c */
int		ms_inc_shlvl(t_m_shl *g, int shlvl);
int		ms_cp_env(t_m_shl *g);

#endif

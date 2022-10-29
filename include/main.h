/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 23:52:26 by csejault          #+#    #+#             */
/*   Updated: 2021/10/26 17:57:41 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "minishell.h"

int		ms_print_error_msg(char *toprint, int code);

/*		ms_free.c */
int		ms_free_xpt(t_m_shl *g);
int		ms_free_path(t_m_shl *g);
int		ms_free_t_env(t_env *data, bool is_error);
int		ms_free(void **tofree);
int		ms_free_s_exec(t_m_shl *g);

/*		ms_free_ms.c */
int		ms_g_errno(void);
int		ms_free_ms(t_m_shl *g);

/*		ms_prompt.c */
int		ms_prompt(t_m_shl *g);

/*		ms_set_default.c */
int		ms_set_default(t_m_shl *g);
void	ms_check_signals(void);

/*		ms_signals.c */
void	ms_set_g_exec_ret(t_m_shl *g, int status);
int		ms_check_sig_fork(void);
int		ms_check_sig_main(void);

#endif

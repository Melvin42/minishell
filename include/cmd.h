/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 22:51:09 by csejault          #+#    #+#             */
/*   Updated: 2021/09/30 15:52:49 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "minishell.h"

/*	ms_pipe.c */
int	ms_create_pipe(t_m_shl *g);
int	ms_close_all_pipe(t_m_shl *g);

/*	ms_fork_cmd_without_pipe.c */
int	ms_fork_cmd_w_no_pipe(t_m_shl *g);

/*	ms_fork_cmd_with_pipe.c */
int	ms_fork_cmd_w_pipe(t_m_shl *g);

/*	ms_exec_cmd.c */
int	ms_set_path(t_m_shl *g);

/*	ms_rafter_action.c */
int	ms_red_double_l(t_m_shl *g);
int	ms_red_simple_l(t_m_shl *g);
int	ms_red_double_r(t_m_shl *g);
int	ms_red_simple_r(t_m_shl *g);

/*	ms_read_input.c */
int	ms_create_file(char ***file, int nb_l, char *eof);

/*	ms_set_path.c */
int	ms_exec_cmd(t_m_shl *g);

/*	ms_set_s_exec.c */
int	ms_set_s_exec(t_m_shl *g);
int	ms_reset_s_exec(t_m_shl *g);

/*	ms_set_args.c */
int	ms_set_args(t_m_shl *g);

/*	ms_redirection.c */
int	ms_redirection(t_m_shl *g);

#endif

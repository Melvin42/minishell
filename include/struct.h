/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:31:44 by csejault          #+#    #+#             */
/*   Updated: 2021/10/07 10:34:00 by csejault         ###   ########.fr       */
/*   Updated: 2021/09/20 14:17:01 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "define.h"

typedef struct s_m_shl	t_m_shl;

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
	struct s_list	*prev;
}t_list;

typedef struct s_read_input
{
	int		fd;
	char	***file;
	char	*eof;
	char	*line;
	t_list	*lst;
	t_list	*n;
}				t_read_input;

typedef struct s_cmd
{
	int		index;
	char	*prev_red;
	char	**cmd;
	int		*red;
}t_cmd;

typedef struct s_path
{
	char	**path;
	char	*path_save;
	int		line;
	int		*len_line;
}t_path;

typedef struct s_env
{
	char	*key;
	char	*val;
}t_env;

typedef struct s_args
{
	int		len;
	int		start;
	char	**inst;
	int		*is_red;
}t_args;

typedef struct s_prompt
{
	char	*pwd;
	char	*line;
}t_prompt;

typedef struct s_redir
{
	int		i;
	char	**inst;
	int		max_l_red;
	int		max_r_red;
	int		l_red_nb;
	int		r_red_nb;
	int		*is_red;
	int		out;
	int		input[2];	
	char	**file;
	int		saveout;
	int		savein;
}t_redir;

typedef struct s_export
{
	char	***srt_env;
	int		env_vers;
}t_export;

typedef struct s_builtin
{
	int		(*fct[NB_BUILTIN])();
	char	*name[NB_BUILTIN];
	char	str_echo[5];
	char	str_cd[3];
	char	str_pwd[4];
	char	str_export[7];
	char	str_unset[6];
	char	str_env[4];
	char	str_exit[5];
}t_builtin;

typedef struct s_pars
{
	char	*start;
	int		pipe_nbr;
	int		ret;
	int		i;
	int		len[3];
	bool	quote[2];
}t_pars;

typedef struct s_exec
{
	int		fdin;
	int		fdout;
	int		builtin_nbr;
	int		*p_fd;
	t_list	*jobs;
	int		job_id;
	char	**full_cmd;
	char	*to_exec;
	char	**args;

}t_exec;

struct s_m_shl
{
	t_builtin	s_builtin;
	t_exec		s_x;
	t_prompt	s_pmt;
	t_path		s_path;
	t_args		s_args;
	t_export	s_xpt;
	t_list		*env[2];
	t_list		*pipe;
	t_pars		p;
	t_redir		s_redir;
	char		**env_ms;
	int			exec_ret;
	int			env_size;
	int			env_vers;
};

#endif

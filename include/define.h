/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 15:42:05 by csejault          #+#    #+#             */
/*   Updated: 2021/10/12 13:12:19 by melperri         ###   ########.fr       */
/*   Updated: 2021/09/20 17:12:13 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define STR_PIPE_ERROR "bash: syntax error near unexpected token `|'"
# define STR_R_RAFTER_ERR "bash: syntax error near unexpected token >'"
# define STR_L_RAFTER_ERR "bash: syntax error near unexpected token <'"
# define STR_DR_RAFTER_ERR "bash: syntax error near unexpected token >>'"
# define STR_DL_RAFTER_ERR "bash: syntax error near unexpected token <<'"
# define STR_NEWLINE_ERR "bash: syntax error near unexpected token newline'"
# define STR_CD_NO_HOME_ERROR "bash: cd: HOME not set"
# define STR_CD_TO_MANY_ARGS_ERROR "cd: string not in pwd"
# define STR_EXIT_TO_MANY_ARGS_ERROR "bash: exit: too many arguments"
# define STR_BAD_CMD ": command not found"
# define STR_UNCLOSED_S_QUOTE "bash: syntax error near unexpected token '"
# define STR_UNCLOSED_D_QUOTE "bash: syntax error near unexpected token \""
# define BUFFER_SIZE 1
# define NB_BUILTIN 7
# define KO 1

enum	e_error {
	MALOC_ERROR = -255,
	PIPE_ERROR,
	CD_NO_HOME_ERROR,
	CD_TO_MANY_ARGS_ERROR,
	EXIT_TO_MANY_ARGS_ERROR,
	RAFTER_NB_ERROR,
	BAD_CMD,
	UNCLOSE_S_QUOTE,
	UNCLOSE_D_QUOTE
};

enum	e_redirect {
	GNL = 0,
	RECURS
};

enum	e_redirecton
{
	RED_S_R = 1,
	RED_S_L,
	RED_D_R,
	RED_D_L
};

enum	e_list {
	FRT = 0,
	BCK
};

enum	e_env {
	KEY = 0,
	VAL
};

enum	e_len {
	SUB = 0,
	ENV,
	MAX
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 13:02:42 by csejault          #+#    #+#             */
/*   Updated: 2021/10/26 16:57:28 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	check_exit_max(char *s1, char *s2)
{
	int		i;

	i = 0;
	if (ms_strlen(s1) == 19)
		while (s1[i] && s2[i] && s1[i] == s2[i])
			i++;
	if (s1[i] > s2[i])
		return (-1);
	else
		return (0);
}

static void	ms_exit_bad_num_arg(t_m_shl *g, char **cmd, int ret)
{
	write (2, "bash: exit: ", 12);
	write (2, cmd[1], ms_strlen(cmd[1]));
	write (2, ": numeric argument required\n", 28);
	ms_free_ms(g);
	exit(ret);
}

static void	ms_chose_exit(t_m_shl *g, char **cmd, int len_split, int ret)
{
	if (len_split < 2)
		;
	else if (len_split > 2)
	{
		ms_print_error_msg(STR_EXIT_TO_MANY_ARGS_ERROR, KO);
		ms_set_g_exec_ret(g, EXIT_TO_MANY_ARGS_ERROR);
		return ;
	}
	else if (ms_str_is_nbr(cmd[1])
		&& ((ms_isdigit(cmd[1][0]) && ms_strlen(cmd[1]) <= 19)
		|| (cmd[1][0] == '-' && ms_strlen(cmd[1]) <= 20))
		&& check_exit_max(cmd[1], "9223372036854775807") == 0)
		;
	else
		ms_exit_bad_num_arg(g, cmd, ret);
	ms_free_ms(g);
	exit(ret);
}

static void	ms_exit_ko(t_m_shl *g, char **cmd, int len_split, long long ret)
{
	int		i;
	int		res;
	char	*str;

	i = -1;
	if (cmd[1])
		res = ms_atoll(cmd[1]);
	if (ms_strlen(cmd[1]) > 20)
	{
		str = cmd[1];
		cmd[1] = ms_lltoa(res);
		free(str);
	}
	if (len_split > 1)
	{
		if (cmd[1][++i] == '-')
			;
		else
			i--;
		while (cmd[1][++i])
			if (!ms_isdigit(cmd[1][i]))
				ms_exit_bad_num_arg(g, cmd, ret);
	}
	ms_chose_exit(g, cmd, len_split, ret);
}

int	ms_exit(t_m_shl *g)
{
	int			len_split;
	char		**cmd;
	long long	ret;

	cmd = g->s_x.args;
	len_split = ms_len_split(cmd);
	ret = 0;
	write(1, "exit\n", 5);
	if (len_split > 2)
		ret = 2;
	else if (len_split == 2)
	{
		ret = ms_atoll(cmd[1]);
		if (ms_str_is_nbr(cmd[1])
			&& ((ms_isdigit(cmd[1][0]) && ms_strlen(cmd[1]) <= 19)
			|| (cmd[1][0] == '-' && ms_strlen(cmd[1]) <= 20)))
			ret = ret % 256;
		else if (ret < 9223372036854775807)
			ret = ret % 256;
		else
			ret = 2;
	}
	ms_exit_ko(g, cmd, len_split, ret);
	return (0);
}

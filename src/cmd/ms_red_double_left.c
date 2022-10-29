/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_red_double_left.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:51:25 by csejault          #+#    #+#             */
/*   Updated: 2021/10/22 18:03:25 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	ms_red_double_l2(t_m_shl *g, int i)
{
	if (pipe(g->s_redir.input))
		return (g_errno = errno);
	if (g->s_redir.file)
	{
		while (g->s_redir.file[i])
		{
			write(g->s_redir.input[1], g->s_redir.file[i],
				ms_strlen(g->s_redir.file[i]));
			write(g->s_redir.input[1], "\n", 1);
			i++;
		}
	}
	close(g->s_redir.input[1]);
	ms_free_split(&g->s_redir.file);
	return (0);
}

int	ms_red_double_l(t_m_shl *g)
{
	char	*eof;
	int		i;

	i = 0;
	g->s_redir.i++;
	g->s_redir.l_red_nb++;
	eof = g->s_redir.inst[g->s_redir.i];
	if (ms_read_file(g, 0, &g->s_redir.file, eof))
	{
		perror("error reading input\n");
		return (g->exec_ret);
	}
	if (!(g->s_redir.l_red_nb == g->s_redir.max_l_red
			&& g->s_redir.l_red_nb > 0))
		ms_free_split(&g->s_redir.file);
	else
	{
		if (ms_red_double_l2(g, i))
			return (g_errno);
	}
	return (0);
}

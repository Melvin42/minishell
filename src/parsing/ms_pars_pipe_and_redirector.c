/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pars_pipe_and_redirector.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 17:25:10 by melperri          #+#    #+#             */
/*   Updated: 2021/10/27 15:46:56 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ms_index_on_space(t_m_shl *g, char *line)
{
	g->p.i = ms_trim_space(line, g->p.i) - 1;
	if ((line[g->p.i + 1] > ' ' && line[g->p.i + 1] < '|')
		|| (line[g->p.i + 1] > '|' && line[g->p.i + 1] < 127)
		|| (line[g->p.i + 1] < '>' && line[g->p.i + 1] > '>')
		|| (line[g->p.i + 1] < '<' && line[g->p.i + 1] > '<'))
	{
		if (ms_ultimate_realloc_split(ms_return_cmd_addr(ms_found_index_node(g,
						g->p.pipe_nbr)),
				g->p.start, ms_search_end_of_word(g->p.start)))
			return (-1);
		g->p.start = line + g->p.i + 1;
	}
	return (0);
}

int	ms_index_on_rafter(t_m_shl *g, char *line)
{
	int	size;

	if (g->p.i > 0 && line[g->p.i - 1] != ' ')
	{
		g->p.i--;
		size = ms_search_end_of_word(g->p.start);
		if (ms_ultimate_realloc_split(ms_return_cmd_addr(ms_found_index_node(g,
						g->p.pipe_nbr)), g->p.start, size))
			return (g_errno);
		g->p.i++;
		g->p.start = line + g->p.i;
	}
	size = ms_count_rafter(g, g->p.start);
	if (size < 0)
		return (g->p.ret);
	if (ms_ultimate_realloc_split(ms_return_cmd_addr(ms_found_index_node(g,
					g->p.pipe_nbr)), g->p.start, size))
		return (g_errno);
	g->p.i += size;
	g->p.i = ms_trim_space(line, g->p.i);
	g->p.start = line + g->p.i;
	g->p.i--;
	return (0);
}

int	ms_check_double_pipe(t_m_shl *g, char *line)
{
	int	i;

	if (line[g->p.i + 1] == '|')
	{
		ms_print_error_msg(STR_PIPE_ERROR, PIPE_ERROR);
		g->p.ret = PIPE_ERROR;
		return (-1);
	}
	i = g->p.i + 1;
	if (line[i] == ' ')
		i = ms_trim_space(line, i);
	if (line[i] == '|')
	{
		ms_print_error_msg(STR_PIPE_ERROR, PIPE_ERROR);
		g->p.ret = PIPE_ERROR;
		return (-1);
	}
	return (0);
}

int	ms_index_on_pipe(t_m_shl *g, char *line)
{
	char	red[3];

	ms_memset(red, 0, sizeof(red));
	red[0] = line[g->p.i];
	g->p.i = ms_trim_space(line, g->p.i);
	if (ms_ultimate_realloc_split(ms_return_cmd_addr(ms_found_index_node(g,
					g->p.pipe_nbr)), g->p.start,
			ms_search_end_of_word(g->p.start)))
		return (errno);
	g->p.pipe_nbr++;
	g->p.i++;
	g->p.i = ms_trim_space(line, g->p.i);
	g->p.start = line + g->p.i;
	if (ms_add_elem_lst_cmd(g, g->p.pipe_nbr))
		return (g_errno);
	ms_add_prev_red(ms_return_prev_red_addr(ms_found_index_node(g,
				g->p.pipe_nbr)), red);
	g->p.i--;
	return (0);
}

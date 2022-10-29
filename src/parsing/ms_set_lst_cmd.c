/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_set_lst_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:58:44 by melperri          #+#    #+#             */
/*   Updated: 2021/10/27 15:51:19 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ms_inside_loop_p_cmd(t_m_shl *g, char *line, bool quote[2])
{
	if ((line[g->p.i] == '>' || line[g->p.i] == '<')
		&& !quote[0] && !quote[1])
	{
		if (ms_count_rafter(g, line + g->p.i) == RAFTER_NB_ERROR)
			return (g->p.ret = RAFTER_NB_ERROR);
		if (ms_index_on_rafter(g, line))
			return (-1);
	}
	else if (line[g->p.i] == ' ' && !quote[0] && !quote[1])
	{
		if (ms_index_on_space(g, line))
			return (-1);
	}
	else if (line[g->p.i] == '\'')
		quote[0] = ms_is_quote_open(quote, 0);
	else if (line[g->p.i] == '\"')
		quote[1] = ms_is_quote_open(quote, 1);
	else if (line[g->p.i] == '|' && !quote[0] && !quote[1])
	{
		if (ms_check_double_pipe(g, line))
			return (PIPE_ERROR);
		if (ms_index_on_pipe(g, line))
			return (-1);
	}
	return (0);
}

static int	ms_loop_p_cmd(t_m_shl *g, char *line, bool quote[2])
{
	while (line[g->p.i])
	{
		if (ms_inside_loop_p_cmd(g, line, quote) != 0)
			return (g->p.ret);
		g->p.i++;
	}
	if (quote[0])
		return (UNCLOSE_S_QUOTE);
	else if (quote [1])
		return (UNCLOSE_D_QUOTE);
	return (0);
}

static int	ms_set_lst_cmd(t_m_shl *g, char *line, bool quote[2])
{
	if (line[0] == '|')
		return (ms_print_error_msg(STR_PIPE_ERROR, PIPE_ERROR));
	g->p.i = 0;
	g->p.ret = ms_check_end_of_line(g);
	if (ms_return_error(g) != 0)
		return (g->p.ret);
	ms_add_elem_lst_cmd(g, g->p.pipe_nbr);
	g->p.i = ms_trim_space(line, g->p.i);
	g->p.start = line + g->p.i;
	g->p.ret = ms_loop_p_cmd(g, line, quote);
	if (ms_return_error(g) != 0)
		return (g->p.ret);
	ms_last_char(g, g->p.start, g->p.i);
	return (0);
}

static int	ms_substitute_loop(t_m_shl *g, char **token)
{
	g->p.i = 0;
	ms_memset(g->p.quote, 0, sizeof(g->p.quote));
	if (ms_substitute_dollar(g, token) != 0)
		return (g_errno);
	g->p.i = 0;
	ms_memset(g->p.quote, 0, sizeof(g->p.quote));
	if (ms_substitute_quote(g, token, 0) != 0)
		return (g_errno);
	return (0);
}

int	ms_create_lst_pipe(t_m_shl *g, char *line)
{
	char	**array;
	int		i;
	t_list	*lst;

	line = ms_check_only_space_line(line);
	if (line == NULL)
		return (g->p.ret = PIPE_ERROR);
	g->p.ret = ms_set_lst_cmd(g, line, g->p.quote);
	if (g->p.ret)
		return (g->p.ret);
	lst = g->pipe;
	while (lst)
	{
		array = ((t_cmd *)lst->data)->cmd;
		g->p.ret = ms_set_redirector_tab(lst, array);
		i = -1;
		if (ms_return_error(g) != 0)
			return (g->p.ret);
		i = -1;
		while (array[++i])
			if (ms_substitute_loop(g, &array[i]) != 0)
				return (g_errno);
		lst = lst->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 13:44:56 by melperri          #+#    #+#             */
/*   Updated: 2021/10/13 11:42:17 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ms_trim_space(char *line, int i)
{
	while (line[i] == ' ')
		i++;
	return (i);
}

bool	ms_is_quote_open(bool quote[2], int c)
{
	if (quote[c] == true)
		return (false);
	else
		return (true);
}

int	ms_last_char(t_m_shl *g, char *start, int i)
{
	char	*line;
	int		len;

	line = g->s_pmt.line;
	len = ms_strlen(line);
	if (i <= len)
	{
		if (len > 1 && line[i] == '\0')
		{
			if (line[i - 1] != ' ')
			{
				ms_ultimate_realloc_split(ms_return_cmd_addr(
						ms_found_index_node(g, g->p.pipe_nbr)), start,
					ms_search_end_of_word(start));
				return (0);
			}
		}
		if (line[i] == '\0')
			ms_ultimate_realloc_split(ms_return_cmd_addr(ms_found_index_node(g,
						g->p.pipe_nbr)), start,
				ms_search_end_of_word(start));
	}
	return (0);
}

int	ms_check_end_of_line(t_m_shl *g)
{
	char	c;
	int		len;

	len = ms_strlen(g->s_pmt.line);
	c = '\0';
	if (len > 0)
		c = g->s_pmt.line[len - 1];
	if (c == '|')
		return (ms_print_error_msg(STR_PIPE_ERROR, PIPE_ERROR));
	else if (c == '<' || c == '>')
		return (ms_print_error_msg(STR_NEWLINE_ERR, RAFTER_NB_ERROR));
	return (0);
}

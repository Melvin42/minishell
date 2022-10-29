/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 17:58:09 by melperri          #+#    #+#             */
/*   Updated: 2021/10/26 17:44:42 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ms_check_only_space_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i] == ' ')
		if (line[i] != ' ')
			break ;
	if (i == (int)ms_strlen(line))
		return (NULL);
	i = ms_strlen(line);
	if (i > 0)
		while (line[--i] == ' ')
			line[i] = '\0';
	return (line);
}

int	ms_check_redirector_tab(int *tab_red, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (i > 0 && tab_red[i] != 0 && tab_red[i - 1] != 0)
		{
			if (tab_red[i] == RED_S_R)
				return (ms_print_error_msg(STR_R_RAFTER_ERR, RAFTER_NB_ERROR));
			else if (tab_red[i] == RED_S_L)
				return (ms_print_error_msg(STR_L_RAFTER_ERR, RAFTER_NB_ERROR));
			else if (tab_red[i] == RED_D_R)
				return (ms_print_error_msg(STR_DR_RAFTER_ERR, RAFTER_NB_ERROR));
			else if (tab_red[i] == RED_D_L)
				return (ms_print_error_msg(STR_DL_RAFTER_ERR, RAFTER_NB_ERROR));
		}
		i++;
	}
	return (0);
}

int	ms_is_missing_quote(t_m_shl *g)
{
	if (g->p.quote[0])
		return (UNCLOSE_S_QUOTE);
	else if (g->p.quote[1])
		return (UNCLOSE_S_QUOTE);
	return (0);
}

int	ms_return_error(t_m_shl *g)
{
	if (g->p.ret == RAFTER_NB_ERROR)
		return (RAFTER_NB_ERROR);
	else if (g->p.ret == PIPE_ERROR)
		return (PIPE_ERROR);
	else if (g->p.ret == UNCLOSE_S_QUOTE)
		return (ms_print_error_msg(STR_UNCLOSED_S_QUOTE, UNCLOSE_S_QUOTE));
	else if (g->p.ret == UNCLOSE_D_QUOTE)
		return (ms_print_error_msg(STR_UNCLOSED_D_QUOTE, UNCLOSE_D_QUOTE));
	else if (g->p.ret == errno)
		return (errno);
	else
		return (0);
}

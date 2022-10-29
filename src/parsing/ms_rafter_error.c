/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_rafter_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 17:56:58 by melperri          #+#    #+#             */
/*   Updated: 2021/09/20 17:15:03 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ms_second_rafter(char *line, int i)
{
	if (line[i - 1] == '>' && line[i] == '<')
		return (ms_print_error_msg(STR_L_RAFTER_ERR, RAFTER_NB_ERROR));
	else if (line[i - 1] == '<' && line[i] == '>')
		return (ms_print_error_msg(STR_NEWLINE_ERR, RAFTER_NB_ERROR));
	return (0);
}

static int	ms_third_rafter(char *line, int i)
{
	if (line[i] == '>' && line[i - 1] == '>' && line[i - 2] == '>')
		return (ms_print_error_msg(STR_R_RAFTER_ERR, RAFTER_NB_ERROR));
	else if (line[i] == '<' && line[i - 1] == '<' && line[i - 2] == '<')
		return (ms_print_error_msg(STR_L_RAFTER_ERR, RAFTER_NB_ERROR));
	else if (line[i] == '<' && line[i - 1] == '>' && line[i - 2] == '>')
		return (ms_print_error_msg(STR_L_RAFTER_ERR, RAFTER_NB_ERROR));
	else if (line[i] == '>' && line[i - 1] == '<' && line[i - 2] == '<')
		return (ms_print_error_msg(STR_R_RAFTER_ERR, RAFTER_NB_ERROR));
	return (0);
}

static int	ms_fourth_rafter(char *line, int i)
{
	if (line[i] == '>' && line[i - 1] == '>'
		&& line[i - 2] == '>' && line[i - 3] == '>')
		return (ms_print_error_msg(STR_DR_RAFTER_ERR, RAFTER_NB_ERROR));
	else if (line[i] == '<' && line[i - 1] == '<'
		&& line[i - 2] == '<' && line[i - 3] == '<')
		return (ms_print_error_msg(STR_DL_RAFTER_ERR, RAFTER_NB_ERROR));
	else if (line[i] == '<' && line[i - 1] == '>'
		&& line[i - 2] == '>' && line[i - 3] == '>')
		return (ms_print_error_msg(STR_R_RAFTER_ERR, RAFTER_NB_ERROR));
	else if (line[i] == '>' && line[i - 1] == '<'
		&& line[i - 2] == '<' && line[i - 3] == '<')
		return (ms_print_error_msg(STR_L_RAFTER_ERR, RAFTER_NB_ERROR));
	return (0);
}

static int	ms_check_index(char *line, int i)
{
	if (i == 1)
	{
		if (ms_second_rafter(line, i) == RAFTER_NB_ERROR)
			return (RAFTER_NB_ERROR);
	}
	else if (i == 2)
	{
		if (line[i + 1] == '>' || line[i + 1] == '<')
			return (0);
		else
			return (ms_third_rafter(line, i));
	}
	else if (i == 3)
	{
		return (ms_fourth_rafter(line, i));
	}
	return (0);
}

int	ms_count_rafter(t_m_shl *g, char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == '>' || line[i] == '<'))
	{
		if (ms_check_index(line, i) == RAFTER_NB_ERROR)
			return (g->p.ret = RAFTER_NB_ERROR);
		i++;
	}
	return (i);
}

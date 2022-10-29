/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_substitute_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:57:20 by melperri          #+#    #+#             */
/*   Updated: 2021/09/23 13:05:33 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ms_realloc_str_without_quote(char **token, int first, int second)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = NULL;
	tmp = malloc(sizeof(tmp) * (ms_strlen(*token) - 1));
	if (tmp == NULL)
		return (ms_g_errno());
	i = -1;
	j = 0;
	while ((*token)[++i])
	{
		if (i == first)
			i++;
		if (i == second)
			i++;
		tmp[j++] = ((*token)[i]);
		if ((*token)[i] == '\0')
			break ;
	}
	tmp[j] = '\0';
	free(*token);
	*token = tmp;
	return (0);
}

static int	ms_check_quote_can_be_close(t_m_shl *g, char *s, int i, int type)
{
	char	c;

	if (type == 0)
		c = '\'';
	else if (type == 1)
		c = '\"';
	while (s[++i])
	{
		if (s[i] == c)
			return (1);
	}
	g->p.quote[type] = ms_is_quote_open(g->p.quote, type);
	return (0);
}

static int	ms_close_quote(t_m_shl *g, char **token, int i_open, int type)
{
	if (ms_realloc_str_without_quote(token, i_open, g->p.i))
		return (-1);
	g->p.i--;
	g->p.quote[type] = ms_is_quote_open(g->p.quote, type);
	return (0);
}

int	ms_open_quote(t_m_shl *g, char *s, int i, int type)
{
	g->p.quote[type] = ms_is_quote_open(g->p.quote, type);
	ms_check_quote_can_be_close(g, s, i, type);
	return (g->p.i);
}

int	ms_substitute_quote(t_m_shl *g, char **s, int i_open)
{
	while ((*s)[g->p.i])
	{
		if ((*s)[g->p.i] == '\'' && !g->p.quote[0] && !g->p.quote[1])
			i_open = ms_open_quote(g, *s, g->p.i, 0);
		else if ((*s)[g->p.i] == '\'' && g->p.quote[0] && !g->p.quote[1])
		{
			if (ms_close_quote(g, s, i_open, 0))
				return (-1);
			continue ;
		}
		else if ((*s)[g->p.i] == '\"' && !g->p.quote[0] && !g->p.quote[1])
			i_open = ms_open_quote(g, *s, g->p.i, 1);
		else if ((*s)[g->p.i] == '\"' && !g->p.quote[0] && g->p.quote[1])
		{
			if (ms_close_quote(g, s, i_open, 1))
				return (-1);
			continue ;
		}
		g->p.i++;
	}
	return (0);
}

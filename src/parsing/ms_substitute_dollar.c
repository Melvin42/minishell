/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_substitute_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 17:05:36 by melperri          #+#    #+#             */
/*   Updated: 2021/10/23 14:02:50 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*ms_replace_interrogation_point(t_m_shl *g, char *src,
		char *dst, char *tosub)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (src[i] && i < g->p.i - 1)
	{
		dst[i] = src[i];
		i++;
		j++;
	}
	k = 0;
	while (k < g->p.len[ENV])
		dst[j++] = tosub[k++];
	i += g->p.len[SUB];
	if (j < g->p.len[MAX])
		while (src[i])
			dst[j++] = src[i++];
	return (dst);
}

static int	ms_interrogation_point(t_m_shl *g, char **token)
{
	char	*tosub;
	char	*join;

	tosub = NULL;
	tosub = ms_itoa(g->exec_ret);
	if (tosub == NULL)
		return (errno);
	join = NULL;
	g->p.len[ENV] = ms_strlen(tosub);
	g->p.len[SUB] = 2;
	g->p.len[MAX] = ms_strlen(*token) + g->p.len[ENV] - 2;
	join = malloc(sizeof(char) * (g->p.len[MAX] + 1));
	if (join == NULL)
		return (-1);
	join[g->p.len[MAX]] = '\0';
	join = ms_replace_interrogation_point(g, *token, join, tosub);
	ms_free((void **)token);
	*token = join;
	ms_free((void **)&tosub);
	g->p.i--;
	if (g->p.len[ENV] != 0)
		g->p.i += g->p.len[ENV] - 1;
	return (0);
}

static int	ms_index_on_dollar(t_m_shl *g, char **token)
{
	char	*tosub;

	tosub = NULL;
	g->p.len[SUB] = 0;
	g->p.i++;
	while ((*token)[g->p.len[SUB] + g->p.i])
	{
		if ((*token)[g->p.len[SUB] + g->p.i] == '?')
		{
			ms_interrogation_point(g, token);
			return (0);
		}
		else if ((*token)[g->p.len[SUB] + g->p.i] == '$'
				|| (*token)[g->p.len[SUB] + g->p.i] == '\"'
				|| (*token)[g->p.len[SUB] + g->p.i] == '\'')
			break ;
		g->p.len[SUB]++;
	}
	tosub = ms_dup_dollar_tosub(g, *token, tosub);
	if (tosub == NULL)
		return (-1);
	if (ms_join_sub(g, token, tosub) == -1)
		return (-1);
	ms_free((void **)&tosub);
	return (0);
}

int	ms_substitute_dollar(t_m_shl *g, char **token)
{
	while ((*token)[g->p.i])
	{
		if ((*token)[g->p.i] == '\'' && !g->p.quote[0])
		{
			g->p.quote[0] = ms_is_quote_open(g->p.quote, 0);
			ms_close_quote_dollar(g, *token, 0);
			if (g->p.i == (int)ms_strlen(*token))
				return (0);
		}
		else if ((*token)[g->p.i] == '$' && (*token)[g->p.i + 1] != '\0'
				&& !g->p.quote[0])
		{
			if (ms_index_on_dollar(g, token) == -1)
				return (errno);
			if (g->p.i < (int)ms_strlen(*token))
				continue ;
			return (0);
		}
		if (((*token)[g->p.i] != '$' && !g->p.quote[0])
				|| ((*token)[g->p.i] == '\'' && g->p.quote[0])
				|| ((*token)[g->p.i] == '"' && g->p.quote[0])
				|| ((*token)[g->p.i + 1] == '\0'))
			g->p.i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_substitute_dollar_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:57:36 by melperri          #+#    #+#             */
/*   Updated: 2021/10/12 16:34:22 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ms_len_env_val(t_list *lst)
{
	int	len;

	if (lst)
		len = ms_strlen(((t_env *)lst->data)->val);
	else
		len = 0;
	return (len);
}

char	*ms_dup_dollar_tosub(t_m_shl *g, char *token, char *tosub)
{
	int	k;

	tosub = malloc(sizeof(char) * (g->p.len[SUB] + 1));
	if (tosub == NULL)
	{
		g_errno = errno;
		return (NULL);
	}
	k = 0;
	while (k < g->p.len[SUB])
	{
		tosub[k] = token[g->p.i + k];
		k++;
	}
	tosub[k] = '\0';
	return (tosub);
}

int	ms_close_quote_dollar(t_m_shl *g, char *token, int type)
{
	int	i;

	i = g->p.i + 1;
	while (token[i])
	{
		if (token[i] == '\'')
			break ;
		i++;
	}
	if (token[i] == '\'')
	{
		if (token[i + 1] == '\'')
			g->p.i += i - g->p.i;
		else
			g->p.i += i - g->p.i + 1;
		g->p.quote[type] = ms_is_quote_open(g->p.quote, type);
	}
	return (0);
}

static char	*ms_replace_dollar(t_m_shl *g, char *src, char *dst, t_list *lst)
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
	if (lst)
	{
		k = 0;
		while (k < g->p.len[ENV])
			dst[j++] = ((t_env *)lst->data)->val[k++];
		i += g->p.len[SUB] + 1;
	}
	if (!lst)
		i += g->p.len[SUB] + 1;
	if (j < g->p.len[MAX])
		while (src[i])
			dst[j++] = src[i++];
	return (dst);
}

int	ms_join_sub(t_m_shl *g, char **token, char *tosub)
{
	char	*join;
	t_list	*lst;

	lst = g->env[0];
	join = NULL;
	while (lst && ms_strcmp(((t_env *)lst->data)->key, tosub) != 0)
		lst = lst->next;
	g->p.len[ENV] = ms_len_env_val(lst);
	g->p.len[MAX] = ms_strlen(*token) + g->p.len[ENV] - g->p.len[SUB] - 1;
	join = malloc(sizeof(char) * (g->p.len[MAX] + 1));
	if (join == NULL)
	{
		g_errno = errno;
		return (-1);
	}
	join[g->p.len[MAX]] = '\0';
	join = ms_replace_dollar(g, *token, join, lst);
	ms_free((void **)token);
	*token = join;
	g->p.i--;
	if (g->p.len[ENV] != 0)
		g->p.i += g->p.len[ENV] - 1;
	return (0);
}

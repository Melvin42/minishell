/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 15:05:21 by melperri          #+#    #+#             */
/*   Updated: 2021/09/27 15:58:43 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

int	ms_search_end_of_word(char *line)
{
	bool	quote[2];
	int		i;

	ms_memset(quote, 0, sizeof(quote));
	i = -1;
	while (line[++i])
	{
		if (line[i] == ' ' && !quote[0] && !quote[1])
			return (i);
		else if (line[i] == '\'')
			quote[0] = ms_is_quote_open(quote, 0);
		else if (line[i] == '\"')
			quote[1] = ms_is_quote_open(quote, 1);
		else if (line[i] == '|' && !quote[0] && !quote[1])
			return (i);
		else if ((line[i] == '<' || line[i] == '>') && !quote[0] && !quote[1])
			return (i);
	}
	return (i);
}

int	ms_ultimate_realloc_split(char ***split, char *start, int size)
{
	char	**tmp;
	int		i;

	i = 0;
	while ((*split)[i])
		i++;
	tmp = NULL;
	tmp = malloc(sizeof(char *) * (i + 2));
	if (tmp == NULL)
		return (-1);
	tmp[i] = malloc(sizeof(char) * (size + 1));
	if (tmp == NULL)
		return (ms_free_one_line_and_split(split, i));
	tmp[i] = ms_strncpy(tmp[i], start, (size + 1));
	tmp[i + 1] = NULL;
	while (--i >= 0)
	{
		tmp[i] = malloc(sizeof(char) * (ms_strlen((*split)[i]) + 1));
		if (tmp[i] == NULL)
			return (ms_free_split_since(split, i));
		tmp[i] = ms_strcpy(tmp[i], (*split)[i]);
	}
	ms_free_split(split);
	*split = tmp;
	return (0);
}

int	ms_add_elem_lst_cmd(t_m_shl *g, int index)
{
	t_cmd	*data;

	data = ms_calloc(sizeof(*data), 1);
	if (!data)
		return (-1);
	data->index = index;
	data->prev_red = ms_calloc(sizeof(data->prev_red), 3);
	if (data->prev_red == NULL)
	{
		g_errno = errno;
		ms_free((void **)data);
		return (-1);
	}
	data->cmd = malloc(sizeof(char *));
	if (data->cmd == NULL)
	{	
		g_errno = errno;
		ms_free((void **)data->prev_red);
		ms_free((void **)data);
		return (-1);
	}
	data->cmd[0] = NULL;
	ms_lstadd_back_cmd(&g->pipe, ms_lstnew_cmd(data));
	return (0);
}

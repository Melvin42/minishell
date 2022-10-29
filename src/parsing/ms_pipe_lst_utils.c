/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe_lst_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 17:05:47 by melperri          #+#    #+#             */
/*   Updated: 2021/09/08 18:55:35 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*ms_found_index_node(t_m_shl *g, int index)
{
	t_list	*lst;

	lst = g->pipe;
	while (((t_cmd *)lst->data)->index != index)
		lst = lst->next;
	return (lst);
}

void	ms_add_prev_red(char **prev_red, char red[3])
{
	int	i;

	i = -1;
	while (red[++i])
		(*prev_red)[i] = red[i];
}

char	**ms_return_prev_red_addr(t_list *lst)
{
	return (&(((t_cmd *)lst->data)->prev_red));
}

char	***ms_return_cmd_addr(t_list *lst)
{
	return (&(((t_cmd *)lst->data)->cmd));
}

void	ms_print_lst_pipe(t_m_shl *g)
{
	t_list	*lst;
	char	**array;
	int		i;

	if (g->pipe)
	{
		lst = g->pipe;
		while (lst)
		{
			i = -1;
			array = ((t_cmd *)lst->data)->cmd;
			dprintf(2, "lst index = %d\n", ((t_cmd *)lst->data)->index);
			dprintf(2, "prev_red = %s\n", ((t_cmd *)lst->data)->prev_red);
			while (array[++i])
				dprintf(2, "%s\n", array[i]);
			lst = lst->next;
		}
	}
}

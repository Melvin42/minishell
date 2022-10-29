/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_read_input2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 10:06:28 by csejault          #+#    #+#             */
/*   Updated: 2021/10/26 17:47:34 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	ms_read_file_error(t_read_input *g, int ret)
{
	t_list	*next;

	g_errno = ret;
	while (g->lst)
	{
		free((char *)g->lst->data);
		g->lst->data = NULL;
		next = g->lst->next;
		free(g->lst);
		g->lst = next;
	}
	ms_free((void **)&g->line);
	return (ret);
}

static void	ms_set_g(t_read_input *g, int fd, char ***file, char *eof)
{
	ms_memset(g, 0, sizeof(*g));
	g->fd = fd;
	g->file = file;
	g->eof = eof;
}

int	ms_transfert_lst_to_tab(t_list *lst, char ***file)
{
	t_list	*next;
	int		i;

	i = 0;
	*file = malloc(sizeof(**file) * (ms_lstsize(lst) + 1));
	if (!*file)
		return (-1);
	while (lst)
	{
		next = lst->next;
		(*file)[i] = lst->data;
		i++;
		ms_free((void **)&lst);
		lst = next;
	}
	(*file)[i] = NULL;
	return (0);
}

int	ms_read_file_job(t_m_shl *sh, t_read_input *g)
{
	g->line = readline(">");
	while (g->line)
	{
		ms_check_sig_fork();
		ms_set_g_exec_ret(sh, 0);
		if (sh->exec_ret == 130 || sh->exec_ret == 131)
		{
			ms_free((void **)&g->line);
			break ;
		}
		if (!ms_strcmp(g->eof, g->line))
		{
			ms_free((void **)&g->line);
			break ;
		}
		g->n = NULL;
		g->n = ms_lstnew(g->line);
		if (!g->n)
			return (-1);
		ms_lstadd_back(&g->lst, g->n);
		g->line = readline(">");
	}
	if (g_errno)
		return (-1);
	return (0);
}

int	ms_read_file(t_m_shl *sh, int fd, char ***file, char *eof)
{
	t_read_input	g;

	if (fd < 0 || !file)
		return (-1);
	ms_set_g(&g, fd, file, eof);
	if (ms_read_file_job(sh, &g))
		return (ms_read_file_error(&g, errno));
	if (ms_transfert_lst_to_tab(g.lst, g.file))
		return (ms_read_file_error(&g, errno));
	return (0);
}

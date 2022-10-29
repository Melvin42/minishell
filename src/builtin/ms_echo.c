/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 12:43:08 by csejault          #+#    #+#             */
/*   Updated: 2021/09/27 13:59:43 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ms_str_only_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ms_echo_with_args(t_m_shl *g, bool *print_cr)
{
	int	i;

	i = 1;
	while (g->s_x.args[i] && g->s_x.args[i][0] == '-')
	{
		if (ms_str_only_n(&g->s_x.args[i][1]))
		{
			*print_cr = false;
			i++;
		}
		else
			break ;
	}
	while (g->s_x.args[i])
	{
		write(1, g->s_x.args[i], ms_strlen(g->s_x.args[i]));
		i++;
		if (g->s_x.args[i])
			write(1, " ", 1);
	}
}

int	ms_echo(t_m_shl *g)
{
	int		i;
	bool	print_cr;

	i = 1;
	print_cr = true;
	if (g->s_x.args[i])
		ms_echo_with_args(g, &print_cr);
	if (print_cr)
		write(1, "\n", 1);
	return (0);
}

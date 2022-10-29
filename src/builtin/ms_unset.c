/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 11:53:58 by csejault          #+#    #+#             */
/*   Updated: 2021/10/23 15:32:08 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ms_unset(t_m_shl *g)
{
	int		i;
	char	**cmd;

	cmd = g->s_x.args;
	i = 1;
	while (cmd[i])
	{
		ms_pop_one_env(g, cmd[i]);
		i++;
	}
	if (ms_cp_env(g) != 0)
		return (-1);
	return (0);
}

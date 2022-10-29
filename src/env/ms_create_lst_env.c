/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_create_lst_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 00:01:49 by csejault          #+#    #+#             */
/*   Updated: 2021/10/13 12:20:20 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
**	For each en line :
**		malloc env
**		split envp in 2 strings (key, value)
**		add to the back of the list g->lst[ENV]
** Split on the first '='
** 
*/

/**WARNING FREE NOT CORRECT **/

int	ms_create_lst_env(t_m_shl *g, char **envp)
{
	int		i;
	t_env	*data;
	t_list	*lst;

	i = 0;
	data = NULL;
	lst = NULL;
	while (envp[i])
	{
		data = malloc(sizeof(*data));
		if (!data)
			return (errno);
		if (ms_split_first_limiter(envp[i], '=', &data->key, &data->val))
			return (errno);
		lst = ms_lstnew(data);
		if (!lst)
			return (errno);
		ms_lstadd_back_env(g, lst);
		i++;
	}
	if (ms_inc_shlvl(g, 0) != 0)
		return (errno);
	return (0);
}

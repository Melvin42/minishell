/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 11:28:11 by csejault          #+#    #+#             */
/*   Updated: 2021/09/27 11:07:57 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*ms_env_find_kval(t_m_shl *g, char *key_to_find)
{
	t_list	*lst;
	t_env	*env;

	lst = g->env[FRT];
	while (lst)
	{
		env = (t_env *)lst->data;
		if (!ms_strcmp(env->key, key_to_find))
			return (env->val);
		lst = lst->next;
	}
	return (NULL);
}

int	ms_env_print_kval(t_m_shl *g, char *key_to_find)
{
	t_list	*lst;
	t_env	*env;
	int		count;

	count = 0;
	lst = g->env[FRT];
	while (lst)
	{
		env = (t_env *)lst->data;
		if (!ms_strcmp(env->key, key_to_find))
		{
			if (!count)
				printf("%s = %s\n", env->key, env->val);
			else
				printf("!!!WARNING TWO KEY!!! %s = %s\n", env->key, env->val);
			count++;
		}
		lst = lst->next;
	}
	if (!count)
		printf("%s not found\n", key_to_find);
	return (0);
}

int	ms_env_update(t_m_shl *g, t_env *data)
{
	t_list	*lst;
	t_env	*env;

	lst = g->env[FRT];
	g->env_vers++;
	while (lst)
	{
		env = (t_env *)lst->data;
		if (!ms_strcmp(env->key, data->key))
		{
			ms_free((void **)&env->val);
			env->val = data->val;
			ms_free((void **)&data->key);
			ms_free((void **)&data);
			return (0);
		}
		lst = lst->next;
	}
	lst = ms_lstnew(data);
	if (!lst)
		return (errno);
	ms_lstadd_back_env(g, lst);
	if (ms_cp_env(g) != 0)
		return (-1);
	return (0);
}

int	ms_env(t_m_shl *g)
{
	t_list	*lst;
	t_env	*env;
	int		fd;

	fd = 1;
	lst = g->env[0];
	while (lst)
	{
		env = ((t_env *)lst->data);
		if (env->key && env->val)
		{
			write(fd, env->key, ms_strlen(env->key));
			write(fd, "=", 1);
			write(fd, env->val, ms_strlen(env->val));
			write(fd, "\n", 1);
		}
		lst = lst->next;
	}
	return (0);
}

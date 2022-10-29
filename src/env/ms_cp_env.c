/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cp_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 12:45:08 by melperri          #+#    #+#             */
/*   Updated: 2021/10/13 12:18:52 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	ms_no_shlvl(t_m_shl *g, t_list *lst, t_env *env)
{
	env = NULL;
	env = malloc(sizeof(*env));
	if (!env)
		return (ms_g_errno());
	env->key = ms_strdup("SHLVL");
	if (env->key == NULL)
		return (ms_g_errno());
	env->val = ms_strdup("1");
	if (env->val == NULL)
		return (ms_g_errno());
	lst = ms_lstnew(env);
	if (!lst)
		return (ms_g_errno());
	ms_lstadd_back_env(g, lst);
	return (0);
}

int	ms_inc_shlvl(t_m_shl *g, int shlvl)
{
	t_list	*lst;
	t_env	*env;

	lst = g->env[FRT];
	while (lst)
	{
		env = (t_env *)lst->data;
		if (ms_strcmp(env->key, "SHLVL") == 0)
		{
			shlvl = ms_atol(env->val) + 1;
			if (shlvl < 0)
				shlvl = 0;
			if (shlvl > INT_MAX)
				shlvl = 1;
			ms_free((void **)&env->val);
			env->val = ms_ltoa(shlvl);
			if (env->val == NULL)
				return (-1);
			return (0);
		}
		lst = lst->next;
	}
	if (ms_no_shlvl(g, lst, env) != 0)
		return (g_errno);
	return (0);
}

static int	ms_strjoin_env(char **dst, char *key, char *val)
{
	int		i;
	char	*tofree;

	tofree = NULL;
	i = ms_strlen(key);
	*dst = ms_strcpy(*dst, key);
	(*dst)[i] = '=';
	(*dst)[i + 1] = '\0';
	tofree = (*dst);
	(*dst) = ms_strjoin(*dst, val);
	if (dst == NULL)
	{
		g_errno = errno;
		ms_free((void **)&tofree);
		return (-1);
	}
	ms_free((void **)&tofree);
	return (0);
}

static int	ms_cp_env_loop(t_m_shl *g, int i)
{
	t_list	*lst;
	t_env	*env;
	int		len;

	lst = g->env[FRT];
	while (lst)
	{
		env = (t_env *)lst->data;
		if (env->key)
			len = ms_strlen(env->key);
		if (env->val)
			len += ms_strlen(env->val);
		g->env_ms[i] = malloc(sizeof(char) * len + 2);
		if (g->env_ms[i] == NULL)
			return (ms_free_split_upside_down(&(g->env_ms), i));
		if (env->key && env->val)
		{
			if (ms_strjoin_env(&g->env_ms[i], env->key, env->val) < 0)
				return (ms_free_split_upside_down(&(g->env_ms), i));
		}
		i++;
		lst = lst->next;
	}
	g->env_ms[i] = NULL;
	return (0);
}

int	ms_cp_env(t_m_shl *g)
{
	if (g->env_ms)
		ms_free_split(&g->env_ms);
	g->env_ms = malloc(sizeof(char *) * (g->env_size + 1));
	if (g->env_ms == NULL)
		return (g_errno = errno);
	if (ms_cp_env_loop(g, 0) != 0)
		return (g_errno);
	return (0);
}

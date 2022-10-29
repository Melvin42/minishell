/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_first_limiter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 00:14:46 by csejault          #+#    #+#             */
/*   Updated: 2021/09/27 11:13:42 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** Split in 2 strings str with the first ecounter of the limiter
*/

static int	ms_fill_fist(char *str, char **first, int len)
{
	*first = malloc(sizeof(**first) * (len + 1));
	if (!*first)
		return (g_errno = errno);
	(*first)[len] = '\0';
	while (--len >= 0)
		(*first)[len] = str[len];
	return (0);
}

static int	ms_fill_second(char *str, char **second, int len)
{
	if (!len)
	{
		*second = NULL;
		return (0);
	}
	*second = malloc(sizeof(**second) * (len + 1));
	if (!*second)
		return (g_errno = errno);
	(*second)[len] = '\0';
	while (--len >= 0)
		(*second)[len] = str[len];
	return (0);
}

int	ms_split_first_limiter(char *str, char limiter, char **first, char **second)
{
	int	len[2];

	len[0] = 0;
	while (str[len[0]] && str[len[0]] != limiter)
		len[0]++;
	len[1] = 0;
	while (str[len[0]] && str[len[0] + 1 + len[1]])
		len[1]++;
	if (ms_fill_fist(str, first, len[0]))
		return (errno);
	if (ms_fill_second(&(str[len[0] + 1]), second, len[1]))
	{
		ms_free((void **)first);
		return (g_errno);
	}
	return (0);
}

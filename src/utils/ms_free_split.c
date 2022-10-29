/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:01:46 by csejault          #+#    #+#             */
/*   Updated: 2021/09/23 13:13:00 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ms_free_split(char ***split)
{
	int	i;

	if (!*split)
		return (-1);
	i = 0;
	while ((*split)[i])
		ms_free((void **)&(*split)[i++]);
	free(*split);
	*split = NULL;
	return (0);
}

int	ms_free_split_upside_down(char ***split, int i)
{
	g_errno = errno;
	if (!*split)
		return (-1);
	while (--i <= 0)
		ms_free((void **)&(*split)[i]);
	free(*split);
	*split = NULL;
	return (-1);
}

int	ms_free_split_since(char ***split, int i)
{
	g_errno = errno;
	if (!*split)
		return (-1);
	while ((*split)[i])
	{
		ms_free((void **)&(*split)[i]);
		i++;
	}
	free(*split);
	*split = NULL;
	return (-1);
}

int	ms_free_one_line_and_split(char ***split, int i)
{
	g_errno = errno;
	if (!*split)
		return (-1);
	ms_free((void **)&(*split)[i]);
	free(*split);
	*split = NULL;
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:25:47 by melperri          #+#    #+#             */
/*   Updated: 2021/09/17 15:25:50 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ms_strjoin(char const *s1, char const *s2)
{
	char		*join;
	size_t		i;
	size_t		j;

	if (!s1 || !s2)
		return (NULL);
	join = NULL;
	join = malloc(sizeof(char) * (ms_strlen(s1) + ms_strlen(s2)) + 1);
	if (join == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	join[i] = '\0';
	return (join);
}

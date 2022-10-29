/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:00:02 by csejault          #+#    #+#             */
/*   Updated: 2021/10/06 12:33:20 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ms_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*ret;

	if (!s)
		return (NULL);
	len = ms_strlen(s);
	ret = malloc(sizeof(*ret) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

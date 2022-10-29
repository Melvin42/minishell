/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 02:08:41 by melperri          #+#    #+#             */
/*   Updated: 2021/07/15 04:22:28 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ms_strncpy(char *dest, const char *src, int n)
{
	int	i;

	i = -1;
	while (src[++i] && i < n - 1)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

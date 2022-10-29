/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strj_fr_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:12:39 by csejault          #+#    #+#             */
/*   Updated: 2021/10/06 12:32:36 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ms_strj_fr_1(char *s1, char const *s2)
{
	char	*ret;

	ret = ms_strjoin(s1, s2);
	if (!ret)
		g_errno = errno;
	if (s1)
		ms_free((void **)&s1);
	return (ret);
}

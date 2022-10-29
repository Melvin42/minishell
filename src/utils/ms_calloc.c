/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 17:42:30 by csejault          #+#    #+#             */
/*   Updated: 2021/06/30 12:34:42 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ms_calloc(size_t nmemb, size_t size)
{
	void	*ret;

	ret = NULL;
	ret = malloc(size * nmemb);
	if (!ret)
		return (NULL);
	ms_bzero(ret, nmemb * size);
	return (ret);
}

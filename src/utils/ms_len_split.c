/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_len_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 14:16:20 by csejault          #+#    #+#             */
/*   Updated: 2021/09/14 13:05:16 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ms_len_split(char **split)
{
	int	len;

	len = 0;
	if (!split)
		return (len);
	while (split[len])
		len++;
	return (len);
}

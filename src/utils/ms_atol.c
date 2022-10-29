/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:43:00 by melperri          #+#    #+#             */
/*   Updated: 2021/10/07 16:47:15 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

long	ms_atol(const char *nptr)
{
	unsigned long	res;
	long			sign;

	res = 0;
	sign = 1;
	while (ms_isspace(*nptr))
		nptr++;
	while (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (ms_isdigit(*nptr))
	{
		res = res * 10 + (*nptr - 48);
		nptr++;
	}
	if (res > LLONG_MAX && sign == -1)
		return (0);
	else if (res > LLONG_MAX && sign == 1)
		return (-1);
	return (res * sign);
}

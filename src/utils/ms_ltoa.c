/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:47:57 by melperri          #+#    #+#             */
/*   Updated: 2021/10/07 16:48:58 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ms_ltoa_len(int n)
{
	unsigned long	nb;
	int				len;

	len = 1;
	if (n < 0)
	{
		nb = -n;
		len++;
	}
	else
		nb = n;
	while (nb >= 10)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ms_ltoa(long n)
{
	unsigned long	nb;
	int				len;
	char			*str;

	str = NULL;
	len = ms_ltoa_len(n);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		nb = -n;
		str[0] = '-';
	}
	else
		nb = n;
	len--;
	while (nb >= 10)
	{
		str[len--] = nb % 10 + 48;
		nb = nb / 10;
	}
	str[len] = nb % 10 + 48;
	return (str);
}

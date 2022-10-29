/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 16:55:22 by melperri          #+#    #+#             */
/*   Updated: 2021/09/14 13:04:57 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ms_itoa_len(int n)
{
	unsigned int	nb;
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

char	*ms_itoa(int n)
{
	unsigned int	nb;
	int				len;
	char			*str;

	str = NULL;
	len = ms_itoa_len(n);
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

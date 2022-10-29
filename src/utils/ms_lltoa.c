/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:17:46 by melperri          #+#    #+#             */
/*   Updated: 2021/10/26 16:58:41 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ms_lltoa_len(int n)
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

char	*ms_lltoa(long long n)
{
	unsigned long	nb;
	int				len;
	char			*str;

	str = NULL;
	len = ms_lltoa_len(n);
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

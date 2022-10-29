/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_print_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:47:42 by csejault          #+#    #+#             */
/*   Updated: 2021/06/28 17:24:09 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ms_print_split(char *name, char **split)
{
	int	i;

	printf("\nBEGIN - %s\n", name);
	i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
	printf("END - %s\nTotal len = %d\n\n", name, i);
}

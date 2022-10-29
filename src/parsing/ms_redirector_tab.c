/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirector_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:46:18 by melperri          #+#    #+#             */
/*   Updated: 2021/10/26 16:22:58 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ms_fill_red_tab(char **array, int **tab_red, int i)
{
	if (ms_strlen(array[i]) == 1)
	{
		if (array[i][0] == '>' && array[i][1] == '\0')
			(*tab_red)[i] = RED_S_R;
		else if (array[i][0] == '<' && array[i][1] == '\0')
			(*tab_red)[i] = RED_S_L;
	}
	else if (ms_strlen(array[i]) == 2)
	{
		if (array[i][0] == '<' && array[i][1] == '<' && array[i][2] == '\0')
			(*tab_red)[i] = RED_D_L;
		else if (array[i][0] == '>' && array[i][1] == '>'
				&& array[i][2] == '\0')
			(*tab_red)[i] = RED_D_R;
	}
}

int	ms_set_redirector_tab(t_list *lst, char **array)
{
	int	*tab_red;
	int	i;
	int	len;

	i = 0;
	while (array[i])
		i++;
	tab_red = NULL;
	tab_red = malloc(sizeof(int) * i);
	if (tab_red == NULL)
		return (g_errno = errno);
	len = i;
	i = -1;
	while (++i < len)
		tab_red[i] = 0;
	i = -1;
	while (++i < len)
		ms_fill_red_tab(array, &tab_red, i);
	((t_cmd *)lst->data)->red = tab_red;
	return (ms_check_redirector_tab(tab_red, len));
}

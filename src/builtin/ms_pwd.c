/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 20:10:08 by csejault          #+#    #+#             */
/*   Updated: 2021/07/30 17:25:45 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ms_pwd(t_m_shl *g)
{
	char	*pwd;

	(void)g;
	pwd = NULL;
	pwd = getcwd(NULL, PATH_MAX);
	if (!pwd)
		return (g_errno = errno);
	else
	{
		write(1, pwd, ms_strlen(pwd));
		write(1, "\n", 1);
		free(pwd);
	}
	return (0);
}

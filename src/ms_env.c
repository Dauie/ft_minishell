/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:24:19 by rlutt             #+#    #+#             */
/*   Updated: 2017/06/19 14:08:30 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int			ms_unsetenv(t_env *shell, t_cmd *info)
{
	int i;
	
	i = 0;
	while (info->av[i])
	{
		if ((unsetenv(info->av[i++])) < 0)
			ft_printf("%s: issue unsetting variable %s\n", G_PROJ, info->av[i]);
	}
	shell->refrshenv = TRUE;
	return (1);
}

int			ms_setenv(t_env *shell, t_cmd *info)
{
	if (info->av[1] && info->av[2])
	{
		setenv(info->av[1], info->av[2], 1);
		shell->refrshenv = TRUE;
	}
	else
		return (-4);
	return (1);
}

void			ms_getenv(t_env *shell, char **environ)
{
	char		**dtmp;

	dtmp = shell->env;
	if (!(shell->env = ft_tbldup(environ, ft_tbllen(environ))))
		return ;
	if (dtmp)
		ft_tbldel(dtmp);
	shell->refrshenv = FALSE;
}

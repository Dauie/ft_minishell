/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 15:32:50 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/21 16:40:18 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void		ms_initinfo(t_shell *info)
{
	info->env = NULL;
	info->av = NULL;
	info->util = NULL;
	info->child = NULL;
	info->uflg = FALSE;
}

static int		ms_initenv(t_shell *info, char **environ)
{
	if (!(getcwd(info->cdir, G_MXDIRLEN)))
		return (-1);
	if (!(info->env = ft_tbldup(environ, ft_tbllen(environ))))
		return (-1);
	ft_printf("%s\n", info->cdir);
	for (int i = 0; info->env[i]; i++)
		ft_printf("%s \n",info->env[i]);
	return (1);
}

int			ms_init(t_shell *info, char **env)
{
	ms_initinfo(info);
	if (!(ms_initenv(info, env)))
	{
		ft_printf("%s: error during environment setup", G_PROJ);
		return (-1);
	}
	else
		return (1);
}

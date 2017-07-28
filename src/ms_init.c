/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 15:32:50 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/27 18:37:27 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void		ms_initinfo(t_cmd *info, t_env *shell)
{
	shell->env = NULL;
	shell->dirstak = NULL;
	shell->homedir = NULL;
	shell->refrshenv = FALSE;
	shell->refrshdir = FALSE;
	info->av = NULL;
	info->util = NULL;
	info->child = 0;
	info->uflg = FALSE;
}

static int		ms_initenv(t_env *shell, char **environ)
{
	if (!(getcwd(shell->curdir, G_MXDIRLEN)))
		return (-1);
	if (!(ms_getdirstak(shell)))
		return (-1);
	if (!(shell->env = ft_tbldup(environ, ft_tbllen(environ))))
		return (-1);
	if (!*shell->env)
	{
		if (!(shell->env = ft_crafttbl(4, "USER=", "PATH=",
			"HOME=", "TMPDIR=")))
			return (-1);
	}
	if (!(shell->homedir = ms_gethome(shell)))
		return (-1);
	ft_strcpy(shell->prevdir, shell->curdir);
	if (!(shell->rootdir = ms_getrootpath(shell)))
		return (-1);
	return (1);
}

int				ms_init(t_cmd *info, t_env *shell, char **env)
{
	ms_initinfo(info, shell);
	if (!(ms_initenv(shell, env)))
	{
		ft_printf("%s: Error during environment setup\n", G_PROJ);
		return (-1);
	}
	else
	{
		ft_printf("(%s)\nv0.7\n", G_PROJ);
		return (1);
	}
}

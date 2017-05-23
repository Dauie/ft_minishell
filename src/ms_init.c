/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 15:32:50 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/22 17:33:25 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void		ms_initinfo(t_cmd *info, t_env *shell)
{
	shell->env = NULL;
	shell->pcdir = NULL;
	shell->homedir = NULL;
	shell->renv = FALSE;
	shell->rdir = FALSE;
	info->av = NULL;
	info->util = NULL;
	info->child = NULL;
	info->uflg = FALSE;
}

char			*ms_getenvar(t_env *shell, char *qry, size_t qlen)
{
	char		*res;
	int			i;

	i = -1;
	res = NULL;
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], qry, qlen) == 0)
			if (!(res = ft_strdup(shell->env[i])))
				return (NULL);
	}
	return (res);
}

void			ms_getpcdir(t_env *shell)
{
	char		**dtmp;
	char		**tmp;
	int			len;

	len = 0;
	dtmp = shell->pcdir;
	if (!(tmp = (char **)ft_strsplit(shell->cdir, '/')))
		return ;
	len = (ft_tbllen(tmp) - 2);
	if (!(shell->pcdir = ft_tbldup(&tmp[len], 2)))
		return ;
	ft_tbldel(tmp);
	if (dtmp)
		ft_tbldel(dtmp);
}

static int		ms_initenv(t_env *shell, char **environ)
{
	if (!(getcwd(shell->cdir, G_MXDIRLEN)))
		return (-1);
	ms_getpcdir(shell);
	if (!(shell->env = ft_tbldup(environ, ft_tbllen(environ))))
		return (-1);
	return (1);
}

int				ms_init(t_cmd *info, t_env *shell, char **env)
{
	ms_initinfo(info, shell);
	if (!(ms_initenv(shell, env)))
	{
		ft_printf("%s: error during environment setup", G_PROJ);
		return (-1);
	}
	else
	{
		ft_putstr("(minishell)\nv0.4\n");
		return (1);
	}
}

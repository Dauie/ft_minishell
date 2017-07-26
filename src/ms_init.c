/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 15:32:50 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/26 12:53:12 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void ms_initinfo(t_cmd *info, t_env *shell)
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

char 		*ms_gethome(t_env *shell)
{
    char 	*homepath;
    char 	*homeparse;

    homeparse = NULL;
    homepath = NULL;
    if (!(homepath = ms_getenvar(shell, "HOME", 4)))
		return (NULL);
    if (!(homeparse = ft_strdup(&homepath[5])))
		return (NULL);
    ft_strdel(&homepath);
    return (homeparse);
}

char 		*ms_getrootpath(t_env *shell)
{
    char 	*homepath;
    char 	*root;
    char 	*end;

    root = NULL;
    homepath = NULL;
    end = NULL;
    if (!(homepath = ms_getenvar(shell, "HOME", 4)))
		return (NULL);
    if (!(end = ft_strchr(homepath, '/')))
		return (NULL);
    *end = '\0';
    if (!(root = ft_strdup(homepath)))
		return (NULL);
    ft_strdel(&homepath);
    return (root);
}

char 		*ms_getenvar(t_env *shell, char *qry, size_t qlen)
{
    char 	*res;
    int 	i;

    i = -1;
    res = NULL;
    if (!qry || !shell)
		return (NULL);
    while (shell->env[++i])
    {
		if (ft_strncmp(shell->env[i], qry, qlen) == 0 && shell->env[i][qlen] == '=')
			if (!(res = ft_strdup(shell->env[i])))
				return (NULL);
    }
    return (res);
}

int			ms_getdirstak(t_env *shell)
{
    char 	**dtmp;
    char 	**tmp;

    dtmp = shell->dirstak;
	tmp = NULL;
	if (ft_strlen(shell->curdir) == 1 && shell->curdir[0] == '/')
	{	
		if (!(shell->util = ft_strdup("/")))
			return (-1);
		if (!(shell->dirstak = ft_tbldup(&shell->util, 1)))
			return (-1);
		ft_strdel(&shell->util);
	}
	else
	{
		if (!(tmp = (char **)ft_strsplit(shell->curdir, '/')))
			return (-1);
 	   if (!(shell->dirstak = ft_tbldup(tmp, ft_tbllen(tmp))))
			return (-1);
    	
	}
	ft_tbldel(tmp, ft_tbllen(tmp));
	if (dtmp)
			ft_tbldel(dtmp, ft_tbllen(dtmp));
	return (1);
}

static int ms_initenv(t_env *shell, char **environ)
{
    if (!(getcwd(shell->curdir, G_MXDIRLEN)))
		return (-1);
    if (!(ms_getdirstak(shell)))
		return (-1);
    if (!(shell->env = ft_tbldup(environ, ft_tbllen(environ))))
		return (-1);
	if (! *shell->env)
		if (!(shell->env = ft_crafttbl(4, "USER=", "PATH=", "HOME=", "TMPDIR=")))
			return (-1);
    if (!(shell->homedir = ms_gethome(shell)))
		return (-1);
    ft_strcpy(shell->prevdir, shell->curdir);
    if (!(shell->rootdir = ms_getrootpath(shell)))
		return (-1);
    return (1);
}

int ms_init(t_cmd *info, t_env *shell, char **env)
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

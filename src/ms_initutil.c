/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_initutil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 18:36:21 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/27 19:02:02 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char			*ms_gethome(t_env *shell)
{
	char		*homepath;
	char		*homeparse;

	homeparse = NULL;
	homepath = NULL;
	if (!(homepath = ms_getenvar(shell, "HOME", 4)))
		return (NULL);
	if (!(homeparse = ft_strdup(&homepath[5])))
		return (NULL);
	ft_strdel(&homepath);
	return (homeparse);
}

char			*ms_getrootpath(t_env *shell)
{
	char		*homepath;
	char		*root;
	char		*end;

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

char			*ms_getenvar(t_env *shell, char *qry, size_t qlen)
{
	char		*res;
	int			i;

	i = -1;
	res = NULL;
	if (!qry || !shell)
		return (NULL);
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], qry, qlen) == 0 &&
			shell->env[i][qlen] == '=')
			if (!(res = ft_strdup(shell->env[i])))
				return (NULL);
	}
	return (res);
}

int				ms_getdirstak(t_env *shell)
{
	char		**dtmp;
	char		**tmp;

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

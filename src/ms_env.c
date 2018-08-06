/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:24:19 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/28 13:48:14 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int			ms_envchgstr_parse(t_cmd *info)
{
	char	**tmp;
	char	**dtmp;

	dtmp = NULL;
	tmp = NULL;
	if (ft_strchr(info->av[1], '='))
	{
		if (!(tmp = ft_strsplit(info->av[1], '=')))
			return (ms_error(-1, NULL));
		dtmp = info->av;
		info->av = ft_crafttbl(3, info->av[0], tmp[0], tmp[1]);
		ft_tbldel(&dtmp);
		ft_tbldel(&tmp);
	}
	return (1);
}

int			ms_unsetenv(t_env *shell, t_cmd *info)
{
	char	**dtmp;

	dtmp = shell->env;
	if (info->av[1])
	{
		if (!(shell->env = ft_tblrmline(shell->env, info->av[1],
			ft_tbllen(shell->env))))
			return (-1);
		ft_tbldel(&dtmp);
	}
	return (1);
}

char		*ms_craft_newenv(const char *name, const char *value)
{
	char	*newenv;

	if (name == NULL || value == NULL)
		return (NULL);
	if (!(newenv = ft_strnew((ft_strlen(name) + 1) + ft_strlen(value))))
		return (NULL);
	ft_strcpy(newenv, (char *)name);
	ft_strcat(newenv, "=");
	ft_strcat(newenv, value);
	return (newenv);
}

int			ms_checkenvdup(t_env *shell, char *qry)
{
	char	*tmp;

	tmp = NULL;
	if ((tmp = ms_getenvar(shell, qry, ft_strlen(qry))))
	{
		ft_strdel(&tmp);
		return (1);
	}
	return (0);
}

int			ms_setenv(t_env *shell, t_cmd *info)
{
	char	*newenv;
	char	**dtmp;

	newenv = NULL;
	dtmp = shell->env;
	if (!info->av[2] && ft_strchr(info->av[1], '='))
		ms_envchgstr_parse(info);
	if (info->av[1] && info->av[2])
	{
		if (ms_checkenvdup(shell, info->av[1]))
			return (ms_error(-5, info->av[1]));
		if (!(newenv = ms_craft_newenv(info->av[1], info->av[2])))
			return (-1);
		if (!(shell->env = ft_tbladdl(shell->env, newenv)))
			return (-1);
		if (dtmp)
			ft_tbldel(&dtmp);
		ft_strdel(&newenv);
		shell->refrshenv = TRUE;
	}
	else
		ms_error(-1, NULL);
	return (1);
}

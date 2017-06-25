/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_findexe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 15:37:02 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/25 21:39:23 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int			ms_checkbin(char *bin, t_cmd *info)
{
	struct dirent	*sd;
	DIR				*dir;
	char			*tmp;

	if (!(dir = opendir(bin)))
		return (0);
	while ((sd = readdir(dir)) != NULL)
	{
		if (ft_strcmp(sd->d_name, info->cmd) == 0)
		{
			tmp = ft_dirjoin(bin, info->cmd);
			ft_bzero(info->cmd, G_MXDIRLEN);
			ft_strcpy(info->cmd, tmp);
			return (1);
		}
	}
	return (1);
}

int			ms_findexe(t_cmd *info, t_env *shell)
{
	char	**bins;
	char	*envpath;
	int		i;

	i = -1;
	if (!(envpath = ms_getenvar(shell, "PATH=", 5)))
		return (0);
	bins = ft_strsplit(envpath, ':');
	while (bins[++i])
	{
		if (!(ms_checkbin(bins[i], info)))
			continue ;
	}
	ft_strdel(&envpath);
	ft_tbldel(bins);
	return (1);
}

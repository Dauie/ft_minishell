/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 21:46:38 by rlutt             #+#    #+#             */
/*   Updated: 2017/06/24 18:43:00 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int	ms_reptilde(t_env *shell, char **av, int i)
{
	char 	buff[G_MXDIRLEN];
	char	*homepath;

	homepath = ms_getenvar(shell, "HOME=", 5);
	ft_strcpy(buff, &homepath[5]);
	ft_strcat(buff, &av[i][1]);
	ft_strdel(&av[i]);
	av[i] = ft_strdup(buff);
	ft_strdel(&homepath);
	return (0);
}

static void ms_prep_envav(t_cmd *info)
{
	char **deltmp;
	char **tmp;

	tmp = NULL;
	deltmp = info->av;
	if (info->av[1] && info->av[2])
		return ;
	else if (info->av[1])
	{
		if (ft_strchr(info->av[1], '='))
		{
			if (!(tmp = ft_strsplit(info->av[1], '=')))
				return ;
			if (tmp[0] && tmp[1])
			{
				free(info->av[1]);
				info->av[1] = tmp[0];
				free(info->av[2]);
				info->av[2] = tmp[1];
			}
		}
		else
			ls_error(4);
	}
}

static void	ms_syntaxhelper(t_cmd *info, t_env *shell)
{
	int	i;

	i = -1;
	if (ft_strcmp(info->av[0], "setenv") == 1)
		ms_prep_envav(info);
	while (info->av[++i])
	{
		if(info->av[i][0] == '~')
			ms_reptilde(shell, info->av, i);
		else
			continue;
	}
	return ;
}

int		ms_parsecmd(t_cmd *info, t_env *shell)
{
	if (!(*info->util))
		return (0);
	if (!(info->av = ft_strsplit(info->util, ' ')))
		return (-1);
	if (info->util)
		ft_strdel(&info->util);
	ft_strcpy(info->cmd, info->av[0]);
	ms_syntaxhelper(info, shell);
	if (ft_strcmp(info->av[0], "exit") == 0)
		exit(1);
	return (1);
}


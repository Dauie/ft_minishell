/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 21:46:38 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/21 11:36:03 by rlutt            ###   ########.fr       */
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

static int ms_repdolla(t_env *shell, char *argstr)
{
	char *tmp;

	tmp = NULL;
	if (!(tmp = ms_getenvar(shell, argstr, ft_strlen(argstr))))
		return (-1);
	else
		argstr = tmp;
	return (0);
}

static void	ms_syntaxhelper(t_cmd *info, t_env *shell)
{
	int	i;

	i = -1;
	while (info->av[++i])
	{
		if(info->av[i][0] == '~')
			ms_reptilde(shell, info->av, i);
		else if (info->av[i][0] == '$')
			ms_repdolla(shell, info->av[i]);
		else
			continue;
	}
	return ;
}

int		ms_parsecmd(t_cmd *info, t_env *shell)
{
	if (!(*info->util))
		return (0);
	if ((ms_checkquotes(info->util)) == -1)
		return(ms_error(-4, NULL));
	if (!(info->av = ft_strsplit(info->util, ' ')))
		return (ms_error(-1, NULL));
	if (info->util)
		ft_strdel(&info->util);
	ft_strcpy(info->cmd, info->av[0]);
	ms_syntaxhelper(info, shell);
	if (ft_strcmp(info->av[0], "exit") == 0)
		exit(1);
	return (1);
}


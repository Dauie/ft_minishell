/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 15:49:45 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/24 17:40:23 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void ms_cd_cleanup(t_env *shell, char *dir)
{
	ft_strcpy(shell->prevdir, shell->curdir);
	ft_bzero(shell->curdir, G_MXDIRLEN);
	getcwd(shell->curdir, G_MXDIRLEN);
	shell->refrshdir = TRUE;
	ft_strdel(&dir);
}

int		ms_cd(t_cmd *info, t_env *shell)
{
	char	*dir;

	if (!(info->av[1]))
	{
		if (!(dir = ft_strdup(shell->homedir)))
			return (-1);
	}
	else if (info->av[1][0] == '-')
	{
		ft_printf("%s\n", shell->prevdir);
		if (!(dir = ft_strdup(shell->prevdir)))
			return (-1);
	}
	else
		if (!(dir = ft_strdup(info->av[1])))
			return (-1);
	if (access(dir, F_OK) == -1)
		return(ms_error(no_such_file, dir));
	if ((chdir(dir) == -1))
		ft_printf("cd: %s error changing directory\n", dir);
	ms_cd_cleanup(shell, dir);
	return (0);
}

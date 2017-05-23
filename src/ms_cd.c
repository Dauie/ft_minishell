/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 15:49:45 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/22 17:31:21 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

//work with how you are parsing the directory now.

static char		*ms_fromhome(t_env *shell, char *dir)
{
	char *home;
	char *ret;
	
	ret = NULL;
	home = NULL;
	if (!(home = ms_getenvar(shell, "HOME=", 5)))
		return (NULL);
	if (!(ret = ft_dirjoin(&home[5], &dir[1])))
		return (NULL);
	ft_strdel(&home);
	return (ret);
}

int			ms_cd(t_cmd *info, t_env *shell)
{
	char	*dir;

	if (info->av[1][0] == '~')
		dir = ms_fromhome(shell, info->av[1]);
	else
		if (!(dir = ft_strdup(info->av[1])))
			return (-1);
	if ((chdir(dir)) < 0)
		ft_printf("cd: no such file or directory: %s\n", dir);
	ft_bzero(shell->cdir, G_MXDIRLEN);
	getcwd(shell->cdir, G_MXDIRLEN);
	shell->rdir = TRUE;
	ft_strdel(&dir);
	return (0);
}

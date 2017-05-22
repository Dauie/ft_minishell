/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 15:49:45 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/22 12:56:56 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

//work with how you are parsing the directory now.

int			ms_cd(t_cmd *info, t_env *shell)
{
	if ((chdir(info->av[1])) < 0)
		ft_printf("cd: no such file or directory: %s\n", info->av[1]);
	ft_bzero(shell->cdir, G_MXDIRLEN);
	getcwd(shell->cdir, G_MXDIRLEN);
	return (0);
}

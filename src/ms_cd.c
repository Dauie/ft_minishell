/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 15:49:45 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/21 16:40:17 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

//work with how you are parsing the directory now.

int			ms_cd(t_shell *info)
{
	if (!(chdir(info->av[1])))
		return (-1);
	ft_bzero(info->cdir, G_MXDIRLEN);
	if (!(getcwd(info->cdir, G_MXDIRLEN)))
		return (-1);
	ft_printf("%s ", info->cdir);
	return (0);
}

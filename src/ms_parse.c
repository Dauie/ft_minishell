/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 21:46:38 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/19 17:33:35 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int		ms_parsecmd(t_shell *info)
{
	ft_strcpy(info->cmd, info->util);
	ft_strdel(&info->util);
	if (ft_strcmp(info->util, "exit") == 0)
		return (0);
	return (1);
}

void		ms_funcmstr(t_shell *info)
{
	info->util++;
}

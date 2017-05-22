/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 21:46:38 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/21 17:33:18 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int		ms_parsecmd(t_cmd *info)
{
	info->av = ft_strsplit(info->util, ' ');
	ft_strdel(&info->util);
	ft_strcpy(info->cmd, info->av[0]);
	if (ft_strcmp(info->av[0], "exit") == 0)
		return (0);
	return (1);
}


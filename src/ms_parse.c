/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 21:46:38 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/22 13:17:23 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int		ms_parsecmd(t_cmd *info)
{
	if (*info->util == '\0')
		return (0);
	if (!(info->av = ft_strsplit(info->util, ' ')))
		return (-1);
	if (info->util)
		ft_strdel(&info->util);
	ft_strcpy(info->cmd, info->av[0]);
	if (ft_strcmp(info->av[0], "exit") == 0)
		return (-1);
	return (1);
}


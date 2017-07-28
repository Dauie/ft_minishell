/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 15:19:14 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/27 19:38:06 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include <stdio.h>

int			ms_echo(t_cmd *info)
{
	int		i;

	i = 1;
	while (info->av[i])
	{
		ft_printf("%s ", info->av[i]);
		i++;
	}
	ft_putchar('\n');
	return (0);
}

int			ms_checkbadarg(char *argstr)
{
	int		i;
	int		len;
	int		cnt;

	len = ft_strlen(argstr);
	i = -1;
	cnt = 0;
	while (argstr[++i])
	{
		if (ft_isspc(argstr[i]))
			cnt++;
	}
	if (cnt == len)
		return (1);
	else
		return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 15:19:14 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/27 18:03:48 by rlutt            ###   ########.fr       */
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

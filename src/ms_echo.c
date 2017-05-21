/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 15:19:14 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/21 15:48:06 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int			ms_echo(t_shell *info)
{
	int		i;

	i = 1;
	while (info->av[i])
		ft_printf("%s ", info->av[i++]);
	ft_putchar('\n');
	return (0);
}

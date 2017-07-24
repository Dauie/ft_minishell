/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 15:19:14 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/22 12:18:32 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include <stdio.h>

int			ms_echo(t_cmd *info)
{
	int		i;
	char 	*print;

	i = 1;
	print = NULL;
	while (info->av[i])
	{	
		if (!(print = ft_strstrip(info->av[i], '"')))
			return(-1);
		ft_printf("%s ", print);
		free(print);
		print = NULL;
		i++;
	}
	ft_putchar('\n');
	return (0);
}

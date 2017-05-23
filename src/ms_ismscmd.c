/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ismscmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:06:06 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/22 13:48:51 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int		ms_ismscmd(char *command)
{
	if (ft_strcmp(command, "cd"))
		return (1);
	else if (ft_strcmp(command, "echo"))
		return (1);
	else if (ft_strcmp(command, "env"))
		return (1);
	else if (ft_strcmp(command, "setenv"))
		return (1);
	else if (ft_strcmp(command, "unsetenv"))
		return (1);
	else
		return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ismscmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:06:06 by rlutt             #+#    #+#             */
/*   Updated: 2017/06/27 09:46:20 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int		ms_ismscmd(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	else if (ft_strcmp(command, "echo") == 0)
		return (1);
	else if (ft_strcmp(command, "env") == 0)
		return (1);
	else if (ft_strcmp(command, "setenv") == 0)
		return (1);
	else if (ft_strcmp(command, "unsetenv") == 0)
		return (1);
	else
		return (0);
}

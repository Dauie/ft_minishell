/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 15:11:25 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/21 16:29:41 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int		ms_execextcmd(t_shell *info)
{
	if ((*info->child = fork()) < 0)
	{
		ft_printf("%s: %s error forking parent process", G_PROJ, info->cmd);
		return (-1);
	}
	else if (*info->child == 0)
	{
		;
	}
	else
	{
		;
	}
	return (1);
}

int		ms_execmscmd(t_shell *info)
{
	if (ft_strcmp(info->cmd, "echo") == 0)
		ms_echo(info);
	else if (ft_strcmp(info->cmd, "cd") == 0)
		ms_cd(info);/*
	else if (ft_strcmp(info->cmd, "setenv"))
		ms_setenv(info);
	else if (ft_strcmp(info->cmd, "unsetenv"))
		ms_unsetenv(info);
	else if (ft_strcmp(info->cmd, "env"))
		ms_putenv(info);*/
	return (0);
}

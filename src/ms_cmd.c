/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 15:11:25 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/22 17:50:11 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int		ms_execextcmd(t_cmd *info)
{
	if ((*info->child = fork()) < 0)
		ft_printf("%s: %s error forking parent process", G_PROJ, info->cmd);
		return (-1);
	return (1);
}

int		ms_execmscmd(t_cmd *info, t_env *shell)
{
	if (ft_strcmp(info->cmd, "echo") == 0)
		ms_echo(info);
	else if (ft_strcmp(info->cmd, "cd") == 0)
		ms_cd(info, shell);
	else if (ft_strcmp(info->cmd, "setenv") == 0)
		ms_setenv(shell, info);
	else if (ft_strcmp(info->cmd, "unsetenv") == 0)
		ms_unsetenv(shell, info);
	else if (ft_strcmp(info->cmd, "env") == 0)
		ms_putenv(shell);
	return (0);
}

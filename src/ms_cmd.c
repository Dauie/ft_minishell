/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 15:11:25 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/24 20:19:40 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int		ms_execextcmd(t_cmd *info, char **env, t_env *shell)
{
	info->child = fork();
	if (info->child < 0)
	{
		ft_printf("%s: %s error forking parent process\n", G_PROJ, info->cmd);
		return (-1);
	}
	else if (info->child > 0)
	{
		waitpid(info->child, &info->status, WUNTRACED);
		while (!WIFEXITED(info->status) && !WIFSIGNALED(info->status))
			waitpid(info->child, &info->status, WUNTRACED);
	}
	else if (info->child == 0)
	{
		ms_findexe(info, shell);
		if (execve(info->cmd, info->av, env) == -1)
		{
			ft_printf("%s: %s is an unknown command\n", G_PROJ, info->av[0]);
			exit(EXIT_FAILURE);
		}
	}
	return (1);
}

int		ms_execmscmd(t_cmd *info, t_env *shell)
{
	if (ft_strcmp(info->cmd, "echo") == 0)
		ms_echo(info);
	else if (ft_strcmp(info->cmd, "cd") == 0)
		ms_cd(info, shell);
	else if (info->av[1] && ft_strcmp(info->cmd, "setenv") == 0)
		ms_setenv(shell, info);
	else if (ft_strcmp(info->cmd, "unsetenv") == 0)
		ms_unsetenv(shell, info);
	else if (ft_strcmp(info->cmd, "env") == 0)
		ms_putenv(shell);
	else if (ft_strcmp(info->cmd, "clear") == 0)
		ms_clear();
	return (0);
}

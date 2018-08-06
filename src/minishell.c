/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 21:02:08 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/27 17:56:18 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void			ms_cleancmd(t_cmd *info)
{
	if (info->av)
		ft_tbldel(&info->av);
	info->av = NULL;
	ft_bzero(info->cmd, G_MXCMDLEN);
}

static void			ms_close(t_cmd *info, t_env *shell)
{
	if (info->av)
		ft_tbldel(&info->av);
	if (info->util)
		ft_strdel(&info->util);
	if (shell->env)
		ft_tbldel(&shell->env);
	if (shell->dirstak)
		ft_tbldel(&shell->dirstak);
}

static void			ms_checkrfrsh(t_env *shell)
{
	if (shell->refrshdir == TRUE)
	{
		if (ms_getdirstak(shell) < 0)
			return ;
		ms_updatepwd(shell);
	}
	ms_putcurdir(shell);
}

static int			ms_run(t_cmd *info, t_env *shell)
{
	ms_checkrfrsh(shell);
	if ((gnl(0, &info->util)) < 0)
		return (-1);
	if ((shell->ret = ms_parsecmd(info, shell)) < 0)
		return (0);
	if (ms_ismscmd(info->cmd) && *info->cmd)
		ms_execmscmd(info, shell);
	else if (*info->cmd)
		ms_execextcmd(info, shell->env, shell);
	ms_cleancmd(info);
	return (1);
}

int					main(void)
{
	t_cmd			info;
	t_env			shell;
	extern char		**environ;

	ms_init(&info, &shell, environ);
	while (1)
	{
		if (ms_run(&info, &shell) < 0)
			break ;
	}
	ms_close(&info, &shell);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 21:02:08 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/20 13:32:19 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void		ms_close(t_cmd *info, t_env *shell);
static void		ms_checkrfrsh(t_env *shell);
static int		ms_run(t_cmd *info, t_env *shell);
static void		ms_cleancmd(t_cmd *info);

int			main(void)
{
	t_cmd		info;
	t_env		shell;
	extern char	**environ;

	ms_init(&info, &shell, environ);
	while (1)
	{
		if (ms_run(&info, &shell) < 0)
			break;
	}
	ms_close(&info, &shell);
}

static int			ms_run(t_cmd *info, t_env *shell)
{
	//INSIDE OF CHKREFRESH YOU NEED TO HAVE IT UPDATE PWD.
	ms_checkrfrsh(shell);
	if ((gnl(0, &info->util)) < 0)
		return (-1);
	if ((shell->ret = ms_parsecmd(info, shell)) < 0)
		return (-1);
	if (ms_ismscmd(info->cmd))
		ms_execmscmd(info, shell);
	else
		ms_execextcmd(info, shell);
	ms_cleancmd(info);
	return (1);
}

static void			ms_cleancmd(t_cmd *info)
{
	ft_tbldel(info->av);
	ft_bzero(info->cmd, G_MXCMDLEN);
}

static void			ms_close(t_cmd *info, t_env *shell)
{
	if (info->av)
		ft_tbldel(info->av);
	if (info->util)
		ft_strdel(&info->util);
	if (shell->env)
		ft_tbldel(shell->env);
	if (shell->dirstak)
		ft_tbldel(shell->dirstak);
}

static void			ms_checkrfrsh(t_env *shell)
{
	if (shell->refrshdir == TRUE)
	{
		ms_getdirstak(shell);
		ms_updatepwd(shell);
	}
	ms_putcurdir(shell);
}

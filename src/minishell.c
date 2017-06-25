/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 21:02:08 by rlutt             #+#    #+#             */
/*   Updated: 2017/06/18 15:27:04 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void		ms_close(t_cmd *info, t_env *shell);
static void		ms_checkrfrsh(t_env *shell, char **environ);
static int		ms_run(t_cmd *info, t_env *shell, char **env);
static void		ms_cleancmd(t_cmd *info);

int			main(void)
{
	t_cmd		info;
	t_env		shell;
	extern char	**environ;

	ms_init(&info, &shell, environ);
	ms_run(&info, &shell, environ);
	ms_close(&info, &shell);
}

static int			ms_run(t_cmd *info, t_env *shell, char **env)
{
	while(1)
	{
		ms_checkrfrsh(shell, env);
		if ((gnl(0, &info->util)) < 0)
			return (-1);
		if ((shell->ret = (ms_parsecmd(info, shell))) < 0)
			break;
		else if (shell->ret == 0)
			continue ;
		if (ms_ismscmd((char *)&info->cmd))
			ms_execmscmd(info, shell);
		else
			ms_execextcmd(info, shell);
		ms_cleancmd(info);
	}
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

static void			ms_checkrfrsh(t_env *shell, char **environ)
{
	if (shell->refrshdir == TRUE)
		ms_getdirstak(shell);
	if (shell->refrshenv == TRUE)
		ms_getenv(shell, environ);
	ms_putcurdir(shell);
}

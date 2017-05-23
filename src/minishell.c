/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <ausdauerr@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 21:02:08 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/22 17:00:05 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void			ms_cleancmd(t_cmd *info)
{
	ft_tbldel(info->av);
	ft_bzero(info->cmd, G_MXCMDLEN);
}

void			ms_close(t_cmd *info, t_env *shell)
{
	if (info->av)
		ft_tbldel(info->av);
	if (info->util)
		ft_strdel(&info->util);
	if (shell->env)
		ft_tbldel(shell->env);
	if (shell->pcdir)
		ft_tbldel(shell->pcdir);
}

void			ms_getenv(t_env *shell, char **environ)
{
	char		**dtmp;

	dtmp = shell->env;
	shell->env = ft_tbldup(environ, ft_tbllen(environ));
	if (dtmp)
		ft_tbldel(dtmp);
	shell->renv = FALSE;
}

void			ms_putcdir(t_env *shell)
{
	int i;

	i = -1;
	ft_putchar('(');
	while (shell->pcdir[++i])
		ft_printf("%s/", shell->pcdir[i]);
	ft_putstr(") $> ");
}

void			ms_checkchng(t_env *shell, char **environ)
{
	if (shell->rdir == TRUE)
		ms_getpcdir(shell);
	if (shell->renv == TRUE)
		ms_getenv(shell, environ);
	ms_putcdir(shell);
}

int				main(void)
{
	t_cmd		info;
	t_env		shell;
	extern char	**environ;
	
	ms_init(&info, &shell, environ);
	while(1)
	{
		ms_checkchng(&shell, environ);
		if ((gnl(0, &info.util)) < 0)
			return (-1);
		if ((shell.ret = (ms_parsecmd(&info))) < 0)
			break;
		else if (shell.ret == 0)
			continue ;
		if (ms_ismscmd((char *)&info.cmd))
			ms_execmscmd(&info, &shell);
		else
			ms_execextcmd(&info);
		ms_cleancmd(&info);
	}
	ms_close(&info, &shell);
}

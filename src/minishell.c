/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <ausdauerr@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 21:02:08 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/22 12:57:20 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void			ms_cleanenv(t_cmd *info)
{
	ft_tbldel(info->av);
	ft_bzero(info->cmd, G_MXCMDLEN);
}

void			ms_putcdir(t_env *shell)
{
	int i;

	i = -1;
	while (shell->pcdir[++i])
		ft_printf("%s/", shell->pcdir[i]);
	ft_putstr(" $> ");
}

void			ms_updatecdir(t_env *shell)
{
	ms_getpcdir(shell);
	ms_putcdir(shell);
}

int				main(void)
{
	t_cmd		info;
	t_env		shell;
	extern char	**environ;
	
	ms_init(&info, &shell, environ);
	ft_putstr("(minishell)\nv0.3\n");
	while(1)
	{
		ms_updatecdir(&shell);
		if ((gnl(0, &info.util)) < 0)
			return (-1);
		if (!(ms_parsecmd(&info)))
			break;
		if (ms_ismscmd((char *)&info.cmd))
			ms_execmscmd(&info, &shell);
		else
			ms_execextcmd(&info);
		ms_cleanenv(&info);
	}
}

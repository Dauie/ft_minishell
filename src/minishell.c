/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <ausdauerr@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 21:02:08 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/21 16:27:10 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void			ms_cleanenv(t_shell *info)
{
	ft_tbldel(info->av);
	ft_bzero(info->cmd, G_MXCMDLEN);
}

int				main(void)
{
	t_shell		info;
	extern char	**environ;
	
	ms_init(&info, environ);
	ft_putstr("(minishell)\nv0.2\n");
	while(1)
	{
		ft_putstr("$> ");
		if ((gnl(0, &info.util)) < 0)
			return (-1);
		if (!(ms_parsecmd(&info)))
			break;
		if (ms_ismscmd((char *)&info.cmd))
			ms_execmscmd(&info);
		else
			ms_execextcmd(&info);
		ms_cleanenv(&info);
	}
}

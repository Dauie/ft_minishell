/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <ausdauerr@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 21:02:08 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/20 15:58:40 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int				main(int ac, char **av, char **environ)
{
	t_shell		info;
	
	ms_init(&info, ac, av, environ);
	ft_putstr("(minishell)\nv0.2\n");
	while(1)
	{
		ft_putstr("$> ");
		if (!(gnl(0, &info.util)))
			return (-1);
		if (!(ms_parsecmd(&info)))
			break;
		if (ms_ismscmd((char *)&info.cmd, &info))
			ms_execmscmd((char *)&info.cmd, &info);
		else
			ms_execextcmd((char *)&info.cmd, &info);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 15:32:50 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/20 15:56:56 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int		ms_initenv(t_shell *info, char **environ)
{
	if (!(info->env = ft_tbldup(environ, ft_tbllen(environ))))
		return (-1);
	else
		return (1);
}

static int		ms_initav(t_shell *info, char **av)
{
	if (!(info->av = ft_tbldup(av, ft_tbllen(av))))
		return (-1);
	else
		return (1);

}

int			ms_init(t_shell *info, char **av, char **env)
{
	if (!(ms_initenv(info, env)))
	{
		ft_printf("%s: error during environment setup", PROJ);
		return (-1);
	}
	if (!(ms_initav(info, av)))
	{
		ft_printf("%s: error during argument parsing", PROJ);
		return (-1);
	}
	return (1);
}

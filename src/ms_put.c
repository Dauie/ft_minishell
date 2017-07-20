/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 13:07:12 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/19 20:03:17 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ms_putenv(t_env *shell)
{
	ft_puttbl(shell->env);
}

void		ms_putcurdir(t_env *shell)
{
	int i;

	i = -1;
	ft_putchar('(');
	if (shell->dirstak)
	{
		while (shell->dirstak[++i])
			ft_printf("%s/", shell->dirstak[i]);
		ft_putstr(") $> ");
	}
}

int		ms_error(t_errc errcode, char *errstr)
{
	if (errcode == access_denied && errstr)
		ft_printf("%s : access is denied\n" G_PROJ);
	else if (errcode == no_such_file)
		ft_printf("cd: no such file or directory: %s\n", errstr);
	else
		ft_printf("General Error\n");
	return (errcode);
}
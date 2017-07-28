/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_checkquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 09:39:52 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/27 18:02:12 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int			ms_checkquotes(char *argstr)
{
	int		i;
	int		flg;

	i = -1;
	flg = 0;
	while (argstr[++i])
	{
		if (argstr[i] == '"' && flg == 0)
			flg = 1;
		else if (argstr[i] == '"' && flg == 1)
			flg = 0;
	}
	return (flg == 0 ? 1 : -1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_changepwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 13:36:03 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/20 14:02:29 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void ms_updatepwd(t_env *shell)
{
	char *newpwd;


	newpwd = NULL;
	if (!(newpwd = ft_strnew(5 + ft_strlen(shell->curdir))))
		return ;
	ft_strcpy(newpwd, "PWD=");
	ft_strcat(newpwd, shell->curdir);
	ft_tblrepline(shell->env, "PWD=", newpwd);
}

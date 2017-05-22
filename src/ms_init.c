/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 15:32:50 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/22 12:48:40 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void		ms_initinfo(t_cmd *info, t_env *shell)
{
	shell->env = NULL;
	shell->pcdir = NULL;
	info->av = NULL;
	info->util = NULL;
	info->child = NULL;
	info->uflg = FALSE;
}

/*void			ms_getusrnamlen(t_env *shell)
{
	int			i;
	
	i = -1;
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], "USER", 4) == 0)
			shell->usrnmlen = ft_strlen(&shell->env[i][6]);
		ft_printf("%i", shell->usrnmlen);
	}
}*/

void			ms_getpcdir(t_env *shell)
{
	char		**tmp;
	int			len;

	len = 0;
	if (!(tmp = (char **)ft_strsplit(shell->cdir, '/')))
		return ;
	len = (ft_tbllen(tmp) - 2);
	shell->pcdir = ft_tbldup(&tmp[len], 2);
		return ;
}

static int		ms_initenv(t_env *shell, char **environ)
{
	if (!(getcwd(shell->cdir, G_MXDIRLEN)))
		return (-1);
	ms_getpcdir(shell);
	if (!(shell->env = ft_tbldup(environ, ft_tbllen(environ))))
		return (-1);
	return (1);
}

int				ms_init(t_cmd *info, t_env *shell, char **env)
{
	ms_initinfo(info, shell);
	if (!(ms_initenv(shell, env)))
	{
		ft_printf("%s: error during environment setup", G_PROJ);
		return (-1);
	}
	else
		return (1);
}

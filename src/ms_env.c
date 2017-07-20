/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:24:19 by rlutt             #+#    #+#             */
/*   Updated: 2017/06/30 11:33:23 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int 		ms_envchgstr_parse(t_cmd *info);

int			ms_unsetenv(t_env *shell, t_cmd *info)
{
	int i;
	
	i = 0;
	while (info->av[i])
	{
		if ((unsetenv(info->av[i++])) < 0)
			ft_printf("%s: issue unsetting variable %s\n", G_PROJ, info->av[i]);
	}
	shell->refrshenv = TRUE;
	return (1);
}

char			*ms_craft_newenv(const char *name, const char *value)
{
	char	*newenv;

	if (name == NULL || value == NULL)
		return (NULL);
	if (!(newenv = ft_strnew((ft_strlen(name) + 1) + ft_strlen(value))))
		return (NULL);
	ft_strcpy(newenv, (char *)name);
	ft_strcat(newenv, "=");
	ft_strcat(newenv, value);
	return (newenv);
}

int				ms_setenv(t_env *shell, t_cmd *info)
{
	char 		*newenv;
	char 		**dtmp;

	newenv = NULL;
	dtmp = shell->env;
	if (!info->av[2] && ft_strchr(info->av[1], '='))
		ms_envchgstr_parse(info);
	if (info->av[1] && info->av[2])
	{
		if (!(newenv = ms_craft_newenv(info->av[1], info->av[2])))
			return (-1);
		if (!(shell->env = ft_tbladdl(shell->env, newenv)))
			return (-1);
		if (dtmp)
			ft_tbldel(dtmp);
		shell->refrshenv = TRUE;
	}
	else
		ms_error(42, NULL);
	return (1);
}

int 		ms_envchgstr_parse(t_cmd *info)
{
	char	**tmp;

	tmp = NULL;
	if (ft_strchr(info->av[1], '='))
	{
		if (!(tmp = ft_strsplit(info->av[1], '=')))
			return (ms_error(42, NULL));
		ft_strdel(&info->av[1]);
		ft_strdel(&info->av[2]);
		info->av[1] = tmp[0];
		info->av[2] = tmp[1];
	}
	return (1);
}


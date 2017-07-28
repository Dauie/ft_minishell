/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parseutil.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 18:56:27 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/27 19:07:28 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int			ms_reptilde(t_env *shell, char **av, int i)
{
	char	buff[G_MXDIRLEN];
	char	*homepath;

	if (!(homepath = ms_getenvar(shell, "HOME", 4)))
		return (-1);
	ft_strcpy(buff, &homepath[5]);
	ft_strcat(buff, &av[i][1]);
	ft_strdel(&av[i]);
	av[i] = ft_strdup(buff);
	ft_strdel(&homepath);
	return (0);
}

int			ms_repdolla(t_env *shell, char **argstr, int i)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	len = ft_strlen(&argstr[i][1]);
	if (!(tmp = ms_getenvar(shell, &argstr[i][1], len)))
		return (-1);
	ft_strdel(&argstr[i]);
	argstr[i] = ft_strdup(&tmp[len + 1]);
	ft_strdel(&tmp);
	return (0);
}

char		*ms_getquote(char *cmdarg)
{
	int		i;
	char	*tmp;
	char	*end;
	char	*res;

	i = -1;
	end = NULL;
	res = NULL;
	tmp = cmdarg;
	if (*tmp == '"')
	{
		tmp++;
		end = ft_strchr(cmdarg + 1, '"');
		if (!(res = ft_strnew(end - tmp)))
			return (NULL);
		while (*tmp && *tmp != '"')
		{
			res[++i] = *tmp;
			tmp++;
		}
	}
	return (res);
}

static int	ms_wordlen(char *cmdstr)
{
	int		len;

	len = 0;
	while (cmdstr[len] && !ft_isspc(cmdstr[len]))
		len++;
	return (len);
}

char		*ms_getword(char *cmdstr)
{
	char	*res;
	int		i;

	i = -1;
	if (!(res = ft_strnew(ms_wordlen(cmdstr))))
		return (NULL);
	while (cmdstr[++i] && !ft_isspc(cmdstr[i]))
		res[i] = cmdstr[i];
	return (res);
}

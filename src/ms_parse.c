/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 21:46:38 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/27 19:06:51 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void	ms_syntaxhelper(t_cmd *info, t_env *shell)
{
	int		i;

	i = -1;
	while (info->av[++i])
	{
		if (info->av[i][0] == '~')
			ms_reptilde(shell, info->av, i);
		else if (info->av[i][0] == '$')
			ms_repdolla(shell, info->av, i);
		else
			continue;
	}
	return ;
}

int			ms_verifycmd(t_cmd *info)
{
	char	*dtmp;

	dtmp = info->util;
	if ((ms_checkquotes(info->util)) == -1)
		return (ms_error(-4, NULL));
	if (!(info->util = ft_strtrim(info->util)))
		return (-1);
	if (dtmp)
		ft_strdel(&dtmp);
	return (1);
}

static int	ms_countargs(char *cmdarg)
{
	size_t	i;
	char	*str;

	i = 0;
	str = cmdarg;
	while (ft_isspc(*str))
		str++;
	if (ft_isascii(*str) || *str == '"')
	{
		i++;
		str++;
	}
	while (*str)
	{
		if (*str == '"' && ((*str - 1) == 0 || (*str - 1) == ' ') && (str + 1))
		{
			i++;
			str = ft_strchr((str + 1), '"');
		}
		else if (*str != ' ' && (*(str - 1) == ' ' || *(str - 1) == 0))
			i++;
		if (str + 1)
			str++;
	}
	return (i);
}

char		**ms_splitcmd(char *cmdarg)
{
	int		i;
	char	**res;
	char	*str;

	res = NULL;
	i = 0;
	if (!(res = ft_memalloc(sizeof(char *) * (ms_countargs(cmdarg) + 1))))
		return (NULL);
	str = cmdarg;
	*str == '"' ? res[i++] = ms_getquote(str) : (0);
	ft_isascii(*str) ? res[i++] = ms_getword(str) : (0);
	if (i > 0)
		str++;
	while (*str && i < ms_countargs(cmdarg))
	{
		if (*str == '"' && ft_isspc(*(str - 1)))
		{
			res[i++] = ms_getquote(str);
			str += ft_strlen(res[i - 1]);
		}
		else if (ft_isascii(*str) && ft_isspc(*(str - 1)))
			res[i++] = ms_getword(str);
		str++;
	}
	return (res);
}

int			ms_parsecmd(t_cmd *info, t_env *shell)
{
	if (!(*info->util))
	{
		ft_strdel(&info->util);
		return (0);
	}
	else
	{
		if ((ms_verifycmd(info)) < 0 || !(*info->util))
			return (-1);
	}
	if (!(info->av = ms_splitcmd(info->util)))
		return (ms_error(-1, NULL));
	if (info->util)
		ft_strdel(&info->util);
	ft_strcpy(info->cmd, info->av[0]);
	ms_syntaxhelper(info, shell);
	if (ft_strcmp(info->av[0], "exit") == 0)
		exit(1);
	return (1);
}

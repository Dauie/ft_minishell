/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 21:46:38 by rlutt             #+#    #+#             */
/*   Updated: 2017/07/24 10:58:38 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int	ms_reptilde(t_env *shell, char **av, int i)
{
	char 	buff[G_MXDIRLEN];
	char	*homepath;

	if (!(homepath = ms_getenvar(shell, "HOME=", 5)))
		return (-1);
	ft_strcpy(buff, &homepath[5]);
	ft_strcat(buff, &av[i][1]);
	ft_strdel(&av[i]);
	av[i] = ft_strdup(buff);
	ft_strdel(&homepath);
	return (0);
}

static int ms_repdolla(t_env *shell, char **argstr, int i)
{
	char *tmp;
	int len;

	tmp = NULL;
	len = ft_strlen(&argstr[i][1]);
	if (!(tmp = ms_getenvar(shell, &argstr[i][1], len)))
		return (-1);
	ft_strdel(&argstr[i]);
	argstr[i] = ft_strdup(&tmp[len + 1]);
	ft_strdel(&tmp);
	return (0);
}

static void	ms_syntaxhelper(t_cmd *info, t_env *shell)
{
	int	i;

	i = -1;
	while (info->av[++i])
	{
		if(info->av[i][0] == '~')
			ms_reptilde(shell, info->av, i);
		else if (info->av[i][0] == '$')
			ms_repdolla(shell, info->av, i);
		else
			continue;
	}
	return ;
}

int 	ms_verifycmd(t_cmd *info)
{
	char *dtmp;

	dtmp = info->util;
	if ((ms_checkquotes(info->util)) == -1)
		return(ms_error(-4, NULL));
	if (!(info->util = ft_strtrim(info->util)))
		return (-1);
	if (dtmp)
		ft_strdel(&dtmp);
	return (1);
}

int 	ms_countargs(char *cmdarg)
{
	size_t	i;
	char	*str;

	i = 0;
	str = cmdarg;
	while (ft_isspc(*str))
		str++;
	if (ft_isalnum(*str) || *str == '"' )
	{
		i++;
		str++;
	}
	while (*str)
	{
		if (*str == '"' && ((*str - 1) == 0 || (*str - 1) == ' '))
		{
			i++;
			str = ft_strchr(str + 1, '"');
		}
		else if ( *str !=  ' ' && (*(str - 1) == ' ' || *(str - 1) == 0))
			i++;
		str++;
	}
return (i);
}

char  *ms_getquote(char *cmdarg)
{
	int i;
	char *tmp;
	char *end;
	char *res;
	
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

int 	ms_wordlen(char *cmdstr)
{
	int len;

	len = 0;
	while (cmdstr[len] && !ft_isspc(cmdstr[len]))
		len++;
	return (len);
}


char *ms_getword(char *cmdstr)
{
	char *res;
	int i;

	i = -1;
	if (!(res = ft_strnew(ms_wordlen(cmdstr))))
		return (NULL);
	while (cmdstr[++i] && !ft_isspc(cmdstr[i]))
		res[i] = cmdstr[i];
	return (res);
}

char 		**ms_splitcmd(char *cmdarg)
{
	int 	i;
	char	**res;
	char	*str;

	res = NULL;
	i = 0;
	if (!(res = ft_memalloc(sizeof(char *) * (ms_countargs(cmdarg) + 1))))
		return (NULL);
	str = cmdarg;
	*str == '"' ? res[i++] = ms_getquote(str) : (0);
	ft_isalnum(*str) ? res[i++] = ms_getword(str) : (0);
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
	return(res);
}

int		ms_parsecmd(t_cmd *info, t_env *shell)
{
	if (!(*info->util))
		return (0);
	else
		if ((ms_verifycmd(info)) < 0 || !(*info->util))
			return (-1);
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


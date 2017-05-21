/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <ausdauerr@gmail.com>				+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 21:03:31 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/21 16:00:11 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/incl/gnl.h"
#include "../libft/incl/str.h"
#include "../libft/incl/put.h"
#include "../libft/incl/tbl.h"

#define G_PROJ "minishell"
#define G_MXNAMLEN 256
#define G_MXCMDLEN 512
#define G_MXDIRLEN 1024

typedef enum	s_mode
{
	mode
}				t_mode;

typedef struct	s_shell
{
	char		**env;
	char		**av;
	char		*util;
	pid_t		*child;
	t_blean		uflg;
	char		cmd[G_MXCMDLEN];
	char		cdir[G_MXDIRLEN];
}				t_shell;

int				ms_init(t_shell *info, char **env);
int				ms_parsecmd(t_shell *info);
int				ms_ismscmd(char *command);
int				ms_execmscmd(t_shell *info);
int				ms_execextcmd(t_shell *info);
int				ms_echo(t_shell *info);
int				ms_cd(t_shell *info);
# endif

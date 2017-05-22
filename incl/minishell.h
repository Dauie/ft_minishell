/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <ausdauerr@gmail.com>				+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 21:03:31 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/22 12:53:32 by rlutt            ###   ########.fr       */
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

typedef struct	s_cmd
{
	char		**av;
	char		*util;
	pid_t		*child;
	t_blean		uflg;
	char		cmd[G_MXCMDLEN];
}				t_cmd;

typedef struct	s_senv
{
	char		**env;
	char		**pcdir;
	char		cdir[G_MXDIRLEN];
	int			usrnmlen;
}				t_env;

int				ms_init(t_cmd *info, t_env *shell, char **env);
void			ms_getpcdir(t_env *shell);
int				ms_parsecmd(t_cmd *info);
int				ms_ismscmd(char *command);
int				ms_execmscmd(t_cmd *info, t_env *shell);
int				ms_execextcmd(t_cmd *info);
int				ms_echo(t_cmd *info);
int				ms_cd(t_cmd *info, t_env *shell);
# endif

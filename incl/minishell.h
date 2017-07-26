/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <ausdauerr@gmail.com>		    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 21:03:31 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/25 20:37:26 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#ifdef __linux__
#include <sys/types.h>
#include <sys/wait.h>
#endif

#include "../libft/incl/gnl.h"
#include "../libft/incl/str.h"
#include "../libft/incl/put.h"
#include "../libft/incl/tbl.h"
#include <dirent.h>

#define G_PROJ "minishell"
#define G_MXNAMLEN 256
#define G_MXCMDLEN 512
#define G_MXDIRLEN 1024

typedef enum s_program_mode {
    continu,
    stop
} t_mode;

typedef enum s_error_code {
 	general_failure = -1,   
	no_such_file = -2,
    access_denied = -3,
	missing_quote = -4,
	duplicate_env = -5

} t_errc;

typedef struct s_cmd
{
    char 		**av;
    char 		*util;
    pid_t 		child;
    int 		status;
    t_blean		uflg;
    char		cmd[G_MXCMDLEN];
} 				t_cmd;

typedef struct s_senv
{
    char		**env;
    t_blean		refrshenv;
    char		**dirstak;
    t_blean		refrshdir;
    int			ret;
    char		curdir[G_MXDIRLEN];
    char		prevdir[G_MXDIRLEN];
    char		*homedir;
    char		*rootdir;
	char		*util;
} 				t_env;

void ms_updatepwd(t_env *shell);
int ms_error(t_errc errcode, char *errstr);
int ms_init(t_cmd *info, t_env *shell, char **env);
int ms_getdirstak(t_env *shell);
char *ms_getenvar(t_env *shell, char *qry, size_t qlen);
void ms_getenv(t_env *shell, char **environ);
int ms_parsecmd(t_cmd *info, t_env *shell);
int ms_ismscmd(char *command);
int ms_execmscmd(t_cmd *info, t_env *shell);
int ms_execextcmd(t_cmd *info, char **env, t_env *shell);
int ms_echo(t_cmd *info);
void ms_putenv(t_env *shell);
void ms_putcurdir(t_env *shell);
void ms_clear(void);
int ms_cd(t_cmd *info, t_env *shell);
int ms_unsetenv(t_env *shell, t_cmd *info);
int ms_setenv(t_env *shell, t_cmd *info);
int ms_findexe(t_cmd *info, t_env *shell);
int	ms_checkquotes(char *argstr);

#endif

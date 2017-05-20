/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <ausdauerr@gmail.com>				+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 21:03:31 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/20 15:58:26 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/incl/gnl.h"
#include "../libft/incl/str.h"
#include "../libft/incl/put.h"
#include "../libft/incl/tbl.h"

#define PROJ "minishell"
#define MXNAMLEN 256
#define MXCMDLEN 512
#define MXDIRLEN 1024

typedef enum	s_mode
{
	mode
}				t_mode;

typedef struct	s_shell
{
	char		**env;
	char		**av;
	char		*util;
	char		cmd[MXCMDLEN];
	char		cdir[MXDIRLEN];
}				t_shell;


int				ms_init(t_shell *info, int ac, char **av, char **env);
int				ms_parsecmd(t_shell *info);
int				ms_ismscmd(char *command, t_shell *info);
int				ms_execmscmd(char *command, t_shell *info);
int				ms_execextcmd(char *command, t_shell *info);
void			ms_funcmstr(t_shell *info);

# endif

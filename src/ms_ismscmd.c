#include "../incl/minishell.h"

int		ms_ismscmd(char *command)
{
	if (ft_strcmp(command, "cd"))
		return (1);
	else if (ft_strcmp(command, "echo"))
		return (1);
	else if (ft_strcmp(command, "env"))
		return (1);
	else if (ft_strcmp(command, "setenv"))
		return (1);
	else if (ft_strcmp(command, "unsetenv"))
		return (1);
	else
		return (0);
}

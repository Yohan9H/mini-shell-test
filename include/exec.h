#ifndef EXEC_H
# define EXEC_H
# include "minishell.h"
#define COMMAND_NOT_FOUND 126
#define IS_A_DIRECTORY 127


typedef struct s_execom
{
	int			pipe_fd[2];
	int			prev_fd;
	int			fdstdin;
	int			fdstdout;
}	t_execom;

#endif
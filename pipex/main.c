/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:23:59 by pmelis            #+#    #+#             */
/*   Updated: 2023/11/23 19:47:55 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

/*
exec:			executes cmd

parameters:		char *cmd
				char **env

return:			void

How it works:	1. sets cmd array with cmd and args
				2. set path to get path of cmd
				3. execute cmd
					4. if failed to exec print error and exit cleanly
*/
void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		write(2, "pipex: command not found: ", 27);
		free(s_cmd);
		exit(1);
	}
}

/*
child:			executes child proccess

parameters:		char **argv
				int *fd
				char **env

return:			void

How it works:	1. open outfile
				2. dups fd of stdin and stdout
				3. closes unused fd
				4. executes cmd
*/
void	child(char **argv, int *fd, char **env)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0777);
	if (infile == -1)
	{
		write(2, "pipex: no such file or directory: ", 35);
		ft_putstr_fd(argv[1], 2);
		write(2, "\n", 1);
		exit(1);
	}
	dup2(infile, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	exec(argv[2], env);
}

/*
parent:			executes parent proccess

parameters:		char **argv
				int *fd
				char **env

return:			void

How it works:	1. open outfile
				2. dups fd of stdin and stdout
				3. closes unused fd
				4. executes cmd
*/
void	parent(char **argv, int *fd, char **env)
{
	int		fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		exit(1);
	dup2(fileout, 1);
	dup2(fd[0], 0);
	close(fd[1]);
	exec(argv[3], env);
}

/*
pipex:			input from infile, 2 cmds and output on outfile

parameters:		int argc
				char **argv
				char **env

return:			int

How it works:	1. If arg != 4 + program name
					2. exit
				3. pipe (fd)
					4. exit if failed
				5. pid = fork
					6. if failed exit
				7. if child process -> initiate child
				8. if parent process -> initiate parent
*/
int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			exit(1);
		if (!pid)
			child(argv, fd, env);
		parent(argv, fd, env);
	}
	else
		write(2, "./pipex infile cmd cmd outfile\n", 32);
	return (1);
}

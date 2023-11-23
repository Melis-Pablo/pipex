/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:12:17 by pmelis            #+#    #+#             */
/*   Updated: 2023/11/22 18:54:09 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h" //mylibft
# include <fcntl.h>		//open = opens file and returns fd
# include <unistd.h>	//close = closes fd
						//read = reads from fd
						//write = writes onto fd
						//access = checks for permissions -1 on denied
						//dup = allocates new fd for oldfd
						//dup2 = replaces std fd's into whatever fd from open(2)
						//execve = ex a program from within your program (repla)
						//fork = creates child process
						//pipe = creates a unidirectional data channel 
						//unlink = removes file (0 if deleted -1 if not)
# include <stdlib.h>	//malloc = allocates memory
						//free = frees memory
						//exit = terminates process
//# include <stdio.h>		//perror = message on stderror
//# include <string.h>	//strerror = returns * to str describes error code
//# include <sys/wait.h>	//wait = waits until child terminates
						//waitpid = waits until specified process terminates

//UTILS.C
char	*get_path(char *cmd, char **env);

#endif

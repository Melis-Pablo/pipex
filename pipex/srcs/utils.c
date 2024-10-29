/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:08:47 by pmelis            #+#    #+#             */
/*   Updated: 2023/11/22 17:59:06 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
my_getenv: 		gets env info

parameters:		char *name
				char **env

return:			char *env

How it works:	1. iterates trough env
				2. skips until = or its done
				3. gets substr until it reached =
				4. if substr = PATH
					5. frees sub
					6. returns current env str in correct spot (after = )
				7. free substr
				8. next iteration
				9. return null
*/
char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (!ft_strcmp(sub, name))
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

/*
get_path:		gets path to cmd

parameters:		char *cmd
				char **env

How it works:	1. set allpath to split, get_env
				2. sets cmd to split cmd and params
				3. goes trough paths
					4. path part = joined path[i] and /
					5. exec = joined path part with cmd
					6. frees pathpart
					7. if success access
						8. free cmd array
						9. returns exec
					10. frees exec
				11. frees allpath
				12. frees s_cmd
				13. return cmd 
*/
char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*pathpart;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		pathpart = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(pathpart, s_cmd[0]);
		free(pathpart);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free(s_cmd);
			return (exec);
		}
		free(exec);
	}
	free(allpath);
	free(s_cmd);
	return (cmd);
}

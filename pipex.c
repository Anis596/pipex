/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:18:44 by abensaid          #+#    #+#             */
/*   Updated: 2025/10/31 08:11:23 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**path;
	char	*path_line;
	char	*tmp;
	int		j;

	path_line = find_path(envp);
	if (!path_line)
		return (NULL);
	path = ft_split(path_line, ':');
	j = 0;
	while (path[j])
	{
		tmp = ft_strjoin(path[j], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (access(tmp, X_OK) == 0)
		{
			free_tab(path);
			return (tmp);
		}
		free(tmp);
		j++;
	}
	free_tab(path);
	return (NULL);
}

void	execute(char *cmd, char **envp)
{
	char	**argv_cmd;
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd, envp);
	if (!cmd_path)
		error_exit("Cmd not found");
	else
	{
		argv_cmd = ft_split(cmd, ' ');
		if (execve(cmd_path, argv_cmd, envp) == -1)
		{
			free_tab (argv_cmd);
			error_exit("execve failed");
		}
	}
}

// int	main(int ac, char **av, char **envp)
//{
//	if (!ac != 2)
//	{
//		write(2, "./a.out \"cmd\"\n", 20);
//		return (1);
//	}
//	exec(av[1]);
//}

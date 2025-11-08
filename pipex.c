/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:18:44 by abensaid          #+#    #+#             */
/*   Updated: 2025/11/08 00:06:14 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**path;
	char	*path_line;
	char	*tmp;
	int		j;

	tmp = get_slash(cmd);
	if (tmp)
		return (tmp);
	path_line = find_path(envp);
	if (!path_line)
		return (NULL);
	path = ft_split(path_line, ':');
	j = 0;
	while (path[j])
	{
		tmp = join_cmd(path[j], cmd);
		if (access(tmp, X_OK) == 0)
		{
			free_tab1(path);
			return (tmp);
		}
		free(tmp);
		j++;
	}
	return (free_tab1(path), NULL);
}

void	execute(char *cmd, char **envp)
{
	char	**argv_cmd;
	char	*cmd_path;

	argv_cmd = ft_split(cmd, ' ');
	cmd_path = get_cmd_path(argv_cmd[0], envp);
	if (!cmd_path)
	{
		free_tab1(argv_cmd);
		error_exit("Cmd not found", 127);
	}
	if (execve(cmd_path, argv_cmd, envp) == -1)
	{
		free_tab1(argv_cmd);
		free(cmd_path);
		error_exit("execve failed", 126);
	}
}

void	child_process_1(int pipe_fd[2], char *file1, char *cmd, char **envp)
{
	int	fd_in;

	fd_in = open(file1, O_RDONLY);
	if (fd_in == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		error_exit("file error", 1);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute(cmd, envp);
}

void	child_process_2(int pipe_fd[2], char *file2, char *cmd, char **envp)
{
	int	fd_out;

	fd_out = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		error_exit("file error", 1);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute(cmd, envp);
}

int	main(int ac, char **av, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	pid1 = 0;
	pid2 = 0;
	if (ac != 5)
		error_exit("Invalid number of arguments", 1);
	pipe(pipe_fd);
	pid1 = fork();
	if (pid1 == 0)
		child_process_1(pipe_fd, av[1], av[2], envp);
	else
		pid2 = fork();
	if (pid2 == 0)
		child_process_2(pipe_fd, av[4], av[3], envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

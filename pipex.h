/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:18:46 by abensaid          #+#    #+#             */
/*   Updated: 2025/10/29 19:56:24 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>    // errno
# include <fcntl.h>    // open
# include <stdio.h>    // perror
# include <stdlib.h>   // malloc, free, exit
# include <string.h>   // strerror
# include <sys/wait.h> // wait, waitpid
# include <unistd.h>   // fork, execve, pipe, dup, dup2, access, close

typedef struct s_pipex
{
	int		pipe_fd[2];
	int		file1;
	int		file2;
	pid_t	pid1;
	pid_t	pid2;
	char	**paths;
	char	**cmd_args;
	char	*cmd_path;
}			t_pipex;

// -------- FONCTIONS PRINCIPALES --------
void		child_process_1(t_pipex *px, char **argv, char **envp);
void		child_process_2(t_pipex *px, char **argv, char **envp);
void		execute(char *cmd, char **envp);
char		*find_path(char *cmd, char **envp);

// -------- UTILS --------
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
void		free_tab(char **tab);
void		error_exit(const char *msg);

#endif

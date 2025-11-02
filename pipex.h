/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:18:46 by abensaid          #+#    #+#             */
/*   Updated: 2025/11/02 14:51:47 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

void	child_process_1(int pipe_fd[2], char *file1, char *cmd, char **envp);
void	child_process_2(int pipe_fd[2], char *file2, char *cmd, char **envp);
void	execute(char *cmd, char **envp);
char	*find_path(char **envp);
char	*get_cmd_path(char *cmd, char **envp);

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
void	free_tab1(char **tab);
void	error_exit(char *msg);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*join_cmd(char *path, char *cmd);

#endif

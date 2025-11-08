/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:40:39 by abensaid          #+#    #+#             */
/*   Updated: 2025/11/08 06:01:31 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
void	error_exit(char *msg, int code);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*join_cmd(char *path, char *cmd);
int		**multi_pipe(int nb_cmds);
void	setup_child(int i, int nb_cmds, int **pipe_nb, char **av, char **envp);
void	run_multi_cmds(int ac, char **av, char **envp);
char	*get_slash(char *cmd);

#endif

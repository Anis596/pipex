/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 23:28:02 by abensaid          #+#    #+#             */
/*   Updated: 2025/11/08 06:00:21 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	**multi_pipe(int nb_cmds)
{
	int	**pipe_nb;
	int	i;

	i = 0;
	pipe_nb = malloc(sizeof(int *) * (nb_cmds - 1));
	if (!pipe_nb)
		error_exit("malloc error", 1);
	while (i < nb_cmds - 1)
	{
		pipe_nb[i] = malloc(sizeof(int) * 2);
		if (!pipe_nb[i])
			error_exit("malloc error", 1);
		if (pipe(pipe_nb[i]) == -1)
			error_exit("pipe error", 1);
		i++;
	}
	return (pipe_nb);
}

void	setup_child(int i, int nb_cmds, int **pipe_nb, char **av, char **envp)
{
	int	j;

	j = 0;
	if (i == 0)
		dup2(open(av[1], O_RDONLY), STDIN_FILENO);
	else
		dup2(pipe_nb[i - 1][0], STDIN_FILENO);
	if (i == nb_cmds - 1)
		dup2(open(av[nb_cmds + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644),
			STDOUT_FILENO);
	else
		dup2(pipe_nb[i][1], STDOUT_FILENO);
	while (j < nb_cmds - 1)
	{
		close(pipe_nb[j][0]);
		close(pipe_nb[j][1]);
		j++;
	}
	execute(av[i + 2], envp);
}

void	run_multi_cmds(int ac, char **av, char **envp)
{
	int		nb_cmds;
	int		**pipe_nb;
	int		i;
	pid_t	pid;

	nb_cmds = ac - 3;
	pipe_nb = multi_pipe(nb_cmds);
	i = 0;
	while (i < nb_cmds)
	{
		pid = fork();
		if (pid == 0)
			setup_child(i, nb_cmds, pipe_nb, av, envp);
		i++;
	}
	while (i < nb_cmds - 1)
	{
		close(pipe_nb[i][0]);
		close(pipe_nb[i][1]);
		i++;
	}
	free(pipe_nb);
	while (wait(NULL) > 0)
		;
}

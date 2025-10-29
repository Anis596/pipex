/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:18:44 by abensaid          #+#    #+#             */
/*   Updated: 2025/10/29 18:38:53 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_pipex(int fd)
{
	char	*str;
	int		newfd;
	char	*cmd1;
	char	*cmd2;

	cmd1 = fork();
	if (!cmd1)
		return (-1);
}

int	exec(char *cmd)
{
	char	**args;

	args = ft_split(cmd, ' ');
}

int	main(int ac, char **av, char **envp)
{
	if (!ac != 2)
	{
		write(2, "./a.out \"cmd\"\n", 20);
		return (1);
	}
	exec(av[1]);
}

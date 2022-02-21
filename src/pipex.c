/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaggana <gtaggana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 00:24:17 by gtaggana          #+#    #+#             */
/*   Updated: 2022/02/21 14:04:12 by gtaggana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	ft_child_p(char	**argv, char **envp, int *fd)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY, 511);
	if (fd_in == -1)
	{
		write (2, "bash: ", 6);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": ", 2);
		ft_error();
	}
	dup2(fd[1], 1);
	dup2(fd_in, 0);
	close(fd[0]);
	ft_solver(argv[2], envp);
}

static void	ft_parent_p(char	**argv, char **envp, int *fd)
{
	int	fd_out;

	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 438);
	if (fd_out == -1)
	{
		write (2, "bash: ", 6);
		write(2, argv[4], ft_strlen(argv[4]));
		write(2, ": ", 2);
		ft_error();
	}
	dup2(fd[0], 0);
	dup2(fd_out, 1);
	close(fd[1]);
	ft_solver(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			ft_error();
		pid = fork();
		if (pid == -1)
			ft_error();
		if (pid == 0)
			ft_child_p(argv, envp, fd);
		else
			ft_parent_p(argv, envp, fd);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		write(2, "Wrong number of args\n", 22);
		exit(1);
	}
	return (0);
}

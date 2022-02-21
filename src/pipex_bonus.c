/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaggana <gtaggana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 00:24:22 by gtaggana          #+#    #+#             */
/*   Updated: 2022/02/21 14:08:27 by gtaggana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	ft_child_p(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_error();
	pid = fork();
	if (pid == -1)
		ft_error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		ft_solver(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, NULL, 0);
	}
}

static void	ft_here_doc(char *limiter)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		ft_error();
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(0);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		wait(NULL);
	}
}

static int	ft_open(char *argv, int i)
{
	int	fd;

	fd = 0;
	if (i == 0)
		fd = open(argv, O_WRONLY | O_CREAT | O_APPEND, 438);
	else if (i == 1)
		fd = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 438);
	else if (i == 2)
		fd = open(argv, O_RDONLY, 511);
	if (fd == -1)
	{
		write (2, "bash: ", 6);
		write(2, argv, ft_strlen(argv));
		write(2, ": ", 2);
		perror("");
		exit(1);
	}
	return (fd);
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	fd_in;
	int	fd_out;

	if ((argc >= 6 && !(ft_strncmp(argv[1], "here_doc", 8))) || argc >= 5)
	{
		i = 2;
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i++;
			fd_out = ft_open(argv[argc - 1], 0);
			ft_here_doc(argv[2]);
		}
		else
		{
			fd_out = ft_open(argv[argc - 1], 1);
			fd_in = ft_open(argv[1], 2);
			dup2(fd_in, 0);
		}
		while (i < argc - 2)
			ft_child_p(argv[i++], envp);
		dup2(fd_out, 1);
		ft_solver(argv[argc - 2], envp);
	}
	ft_finish(argc, argv);
}

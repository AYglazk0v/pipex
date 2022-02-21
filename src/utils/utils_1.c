/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaggana <gtaggana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 00:24:35 by gtaggana          #+#    #+#             */
/*   Updated: 2022/02/15 08:44:12 by gtaggana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	ft_strlen(const char *s)
{
	int	n;

	n = 0;
	while (*(s + n))
		n++;
	return (n);
}

static char	*ft_find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*tmp_path;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 5) == 0)
		i++;
	paths = ft_split(&(envp[i][5]), ':');
	i = -1;
	while (paths[++i])
	{
		tmp_path = ft_px_strjoin(paths[i], "/");
		path = ft_free_strjoin(tmp_path, cmd);
		if (access(path, 0) == 0 || access(cmd, 0) == 0)
		{
			ft_free_dict(paths, -1);
			if (access(cmd, 0) == 0)
				return (cmd);
			return (path);
		}
		free(path);
	}
	ft_free_dict(paths, -1);
	return (NULL);
}

void	ft_solver(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = ft_find_path(cmd[0], envp);
	if (!path)
	{
		write(2, "bash: ", 6);
		write(2, argv, ft_strlen(argv));
		write(2, ": command not found\n", 20);
		ft_free_dict(cmd, -1);
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		ft_free_dict(cmd, -1);
		ft_error();
	}
	ft_free_dict(cmd, -1);
	free(path);
}

static char	*ft_gnl_join(char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i])
		i++;
	str = (char *)malloc(i + 2);
	if (!str)
		return (NULL);
	i = -1;
	while (s[++i])
		str[i] = s[i];
	str[i] = c;
	str[i + 1] = '\0';
	free(s);
	return (str);
}

int	get_next_line(char **line)
{
	char	*buff;
	int		fd;

	if (!line)
		return (-1);
	buff = (char *)malloc(2);
	if (!buff)
		return (-1);
	*line = (char *)malloc(1);
	if (!(*line))
		return (-1);
	*line[0] = '\0';
	fd = 1;
	while (fd > 0)
	{
		fd = read(0, buff, 1);
		*line = ft_gnl_join(*line, buff[0]);
		if (buff[0] == '\n')
			break ;
	}
	free(buff);
	return (fd);
}

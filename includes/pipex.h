/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaggana <gtaggana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 00:24:02 by gtaggana          #+#    #+#             */
/*   Updated: 2022/02/15 08:57:30 by gtaggana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

//ft_split.c

char	**ft_split(char const *s, char c);

//utils_0.c

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_px_strjoin(char const *s1, char const *s2);
char	*ft_free_strjoin(char *s1, char *s2);
void	ft_free_dict(char **dict, int i);

//utils_1.c

int		ft_strlen(const char *s);
void	ft_solver(char *argv, char **envp);
int		get_next_line(char **line);

//utils_2.c
void	ft_finish(int argc, char **argv);
void	ft_error(void);

#endif

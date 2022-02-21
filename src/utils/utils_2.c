/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaggana <gtaggana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 09:01:31 by gtaggana          #+#    #+#             */
/*   Updated: 2022/02/18 13:47:05 by gtaggana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	ft_error(void)
{
	perror("");
	exit(127);
}

void	ft_finish(int argc, char **argv)
{
	if (!((argc >= 6 && !(ft_strncmp(argv[1], "here_doc", 8))) || argc >= 5))
	{
		write(2, "Wrong number of args\n", 22);
		exit(1);
	}
	else
		exit(0);
}

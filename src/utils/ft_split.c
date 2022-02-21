/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaggana <gtaggana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 12:27:05 by gtaggana          #+#    #+#             */
/*   Updated: 2022/02/13 12:27:07 by gtaggana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static char	**ft_clear(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return ((void *)0);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;

	i = 0;
	if (!s)
		return ((void *)0);
	if ((unsigned int)ft_strlen(s) < start)
	{
		sub = malloc(sizeof(char) * 1);
		sub[0] = '\0';
		return (sub);
	}
	if ((unsigned int)ft_strlen(s) - start < len)
		len = (unsigned int)ft_strlen(s) - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return ((void *)0);
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

static size_t	ft_strlen2sep(const char *str, char sep)
{
	size_t			i;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	return (i);
}

static size_t	ft_count_words(const char *str, char sep)
{
	size_t			i;
	size_t			count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] != sep && str[i + 1] && str[i + 1] == sep)
			|| (str[i] != sep && !str[i + 1]))
			count++;
		i++;
	}
	return (count);
}

/*
	The function takes a string and splits it into substrings by separator.
*/
char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	start;
	char	**dict;

	i = 0;
	start = 0;
	if (!s)
		return ((void *)0);
	dict = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (dict == NULL)
		return ((void *)0);
	while (s[i++] == c)
		start++;
	i = -1;
	while (++i < ft_count_words(s, c))
	{
		dict[i] = ft_substr(s, start, ft_strlen2sep(&s[start], c));
		if (dict == NULL)
			return (ft_clear(dict));
		start += ft_strlen2sep(&s[start], c);
		while (s[start] == c)
			start++;
	}
	dict[i] = ((void *)0);
	return (dict);
}

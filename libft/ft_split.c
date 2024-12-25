/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:01:24 by rsebasti          #+#    #+#             */
/*   Updated: 2024/12/25 20:41:59 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	lento(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*strndup(char const *s, size_t n)
{
	char		*nstr;
	size_t		i;

	nstr = malloc((n + 1) * sizeof(char));
	if (nstr == NULL)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		nstr[i] = s[i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}

static size_t	countwords(char const *s, char c)
{
	size_t	nb;
	size_t	i;

	i = 0;
	nb = 0;
	if (s[i] != c && s[i])
		nb++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			nb++;
		i++;
	}
	return (nb);
}

char	**killsplit(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	tab = malloc((countwords(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			tab[n] = strndup(&s[i], lento(&s[i], c));
			if (!tab[n])
				return (killsplit(tab));
			i += lento(&s[i], c) - 1;
			n++;
		}
		i++;
	}
	tab[n] = NULL;
	return (tab);
}

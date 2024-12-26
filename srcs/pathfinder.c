/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:54:06 by rsebasti          #+#    #+#             */
/*   Updated: 2024/12/26 16:25:51 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_word(char **env, char *word)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], word, (int) ft_strlen(word)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static char	*clean_word(char **env, char *word)
{
	int		i;
	int		j;

	i = find_word(env, word);
	j = 0;
	while (env[i][j] && env[i][j] != '=')
		j++;
	return (env[i] + j + 1);
}

char	*search_path(char **env, char *cmd)
{
	int		i;
	char	**split;
	char	*path;

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	split = ft_split(clean_word(env, "PATH"), ':');
	while (split[i])
	{
		path = ft_strdoublejoin(split[i], "/", cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_split(split);
			return (path);
		}
		if (path)
			free(path);
		i++;
	}
	if (split)
		free_split(split);
	return (NULL);
}

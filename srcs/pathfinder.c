/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:54:06 by rsebasti          #+#    #+#             */
/*   Updated: 2024/12/26 14:03:06 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_path(char **env, char *word)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] == word[j])
			j++;
		if (env[i][j] == '=' && word[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

static char	*clean_path(char **env)
{
	int		i;
	int		j;

	i = find_path(env, "PATH");
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
	split = ft_split(clean_path(env), ':');
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

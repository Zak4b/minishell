/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:54:06 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/26 19:10:29 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_path(t_vars *vars, char *cmd)
{
	int		i;
	char	**split;
	char	*env_path;
	char	*path;

	if (cmd == NULL)
		return (NULL);
	if (access(cmd, F_OK) == 0 && ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	env_path = getenv_value(vars, "PATH");
	if (!env_path)
		return (NULL);
	split = ft_split(env_path, ':');
	free(env_path);
	i = 0;
	while (split[i])
	{
		path = ft_strnjoin((char *[]){split[i++], cmd}, 2, "/");
		if (access(path, F_OK | X_OK) == 0)
			return (free_split(split), path);
		free(path);
	}
	return (free_split(split), NULL);
}

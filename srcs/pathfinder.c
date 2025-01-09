/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:54:06 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/09 14:21:15 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_getenv(t_vars *vars, char *word)
{
	t_list	*env;

	env = vars->env;
	while (env)
	{
		if (strcmp(((char **)env->content)[0], word) == 0)
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

char	*getenv_value(t_vars *vars, char *word)
{
	char	**env;

	env = ft_getenv(vars, word);
	if (env)
		return (env[1]);
	return (NULL);
}

char	*search_path(t_vars *vars, char *cmd)
{
	int		i;
	char	**split;
	char	*path;
	char	*join_data[2];

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0 && ft_strncmp(cmd, "./", 2) == 0)
		return (ft_strdup(cmd));
	split = ft_split(getenv_value(vars, "PATH"), ':');

	join_data[1] = cmd;
	while (split[i])
	{
		join_data[0] = split[i];
		path = ft_strnjoin(join_data, 2, "/");
		if (access(path, F_OK | X_OK) == 0)
			return (free_split(split), path);
		free(path);
		i++;
	}
	if (split)
		free_split(split);
	return (NULL);
}

int	correct_path(t_vars *vars, char *cmd)
{
	int		valid;
	char	*res;
	res = search_path(vars, cmd);
	valid = !!res;
	free(res);
	return (valid);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:54:06 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/14 16:31:47 by rsebasti         ###   ########.fr       */
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

char	*getenv_value(t_vars *vars, char *key, bool dup)
{
	char	**env;

	env = ft_getenv(vars, key);
	if (env)
	{
		if (dup)
			return (ft_strdup(env[1]));
		else
			return (env[1]);
	}
	return (NULL);
}

char	*search_path(t_vars *vars, char *cmd)
{
	int		i;
	char	**split;
	char	*env_path;
	char	*path;
	char	*join_data[2];

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0 && ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	env_path = getenv_value(vars, "PATH", false);
	if (!env_path)
		return (NULL);
	split = ft_split(env_path, ':');
	join_data[1] = cmd;
	while (split[i])
	{
		join_data[0] = split[i++];
		path = ft_strnjoin(join_data, 2, "/");
		if (access(path, F_OK | X_OK) == 0)
			return (free_split(split), path);
		free(path);
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

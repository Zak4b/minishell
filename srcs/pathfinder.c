/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:54:06 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/07 16:49:53 by asene            ###   ########.fr       */
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

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0 && ft_strncmp(cmd, "./", 2) == 0)
		return (ft_strdup(cmd));
	split = ft_split(getenv_value(vars, "PATH"), ':');
	while (split[i])
	{
		path = ft_strdoublejoin(split[i], "/", cmd);
		if (access(path, F_OK | X_OK) == 0)
			return (free_split(split), path);
		if (path)
			free(path);
		i++;
	}
	if (split)
		free_split(split);
	return (NULL);
}

int	correct_path(t_vars *vars, char *cmd)
{
	int		i;
	char	**split;
	char	*path;

	i = 0;
	split = ft_split(getenv_value(vars, "PATH"), ':');
	if (access(cmd, F_OK | X_OK) == 0 && strncmp(cmd, "./", 2) == 0)
		return (2);
	while (split[i])
	{
		path = ft_strdoublejoin(split[i], "/", cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			free(path);
			return (1);
		}
		if (path)
			free(path);
		i++;
	}
	if (split)
		free_split(split);
	return (0);
}

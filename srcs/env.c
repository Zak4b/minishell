/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:09:56 by rsebasti          #+#    #+#             */
/*   Updated: 2024/12/27 14:04:59 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_line(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	env_parser(char **env, t_vars *vars)
{
	char	**new_env;
	int		i;

	vars->envsize = count_line(env);
	new_env = malloc(sizeof(char *) * (vars->envsize + 13));
	if (!new_env)
		return ;
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	vars->env = new_env;
}

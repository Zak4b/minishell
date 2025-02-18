/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 21:34:32 by asene             #+#    #+#             */
/*   Updated: 2025/02/18 14:08:57 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_vars *vars, t_exec *data)
{
	t_list	*env;
	char	**value;

	(void)data;
	if (data->argc > 1)
		return (ft_fprintf(2, "env: too many arguments\n"), BAD_USAGE);
	env = vars->env;
	while (env)
	{
		value = env->content;
		ft_fprintf(data->fd_out, "%s=%s\n", value[0], value[1]);
		env = env->next;
	}
	return (0);
}

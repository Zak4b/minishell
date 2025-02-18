/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:09:56 by rsebasti          #+#    #+#             */
/*   Updated: 2025/02/18 14:12:36 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_env(char **env, t_vars *vars)
{
	t_list	*env_lst;
	t_list	*e;
	int		i;
	char	*pos;

	env_lst = NULL;
	i = 0;
	while (env[i])
	{
		e = ft_lstnew(ft_calloc(3, sizeof(char *)));
		pos = ft_strchr(env[i], '=');
		((char **)e->content)[0] = ft_substr(env[i], 0, pos - env[i]);
		((char **)e->content)[1] = ft_strdup(pos + 1);
		ft_lstadd_back(&env_lst, e);
		i++;
	}
	vars->env = env_lst;
}

char	**build_env(t_vars *vars)
{
	int		i;
	t_list	*env;
	char	**res;

	env = vars->env;
	res = ft_calloc(ft_lstsize(env) +1, sizeof(char *));
	i = 0;
	while (env)
	{
		res[i++] = ft_strnjoin(env->content, 2, "=");
		env = env->next;
	}
	return (res);
}

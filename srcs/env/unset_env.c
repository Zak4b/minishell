/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:11:01 by asene             #+#    #+#             */
/*   Updated: 2025/02/18 14:11:10 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_env(t_vars *vars, char *key)
{
	t_list	*env;
	t_list	*prev;
	char	**content;

	env = vars->env;
	prev = NULL;
	while (env)
	{
		content = env->content;
		if (ft_strcmp(content[0], key) == 0)
		{
			if (prev)
				prev->next = env->next;
			else
				vars->env = env->next;
			free_split(content);
			free(env);
			break ;
		}
		prev = env;
		env = env->next;
	}
}
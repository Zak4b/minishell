/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:09:37 by asene             #+#    #+#             */
/*   Updated: 2025/02/18 14:10:04 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(t_vars *vars, char *key, char *value)
{
	t_list	*env;
	char	**content;

	if (value == NULL)
		value = "";
	env = vars->env;
	while (env)
	{
		content = (char **)env->content;
		if (ft_strcmp(content[0], key) == 0)
		{
			if (content[1] != NULL)
				free(content[1]);
			content[1] = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	content = ft_calloc(3, sizeof(char *));
	content[0] = ft_strdup(key);
	content[1] = ft_strdup(value);
	ft_lstadd_back(&vars->env, ft_lstnew(content));
}
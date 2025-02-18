/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:12:45 by asene             #+#    #+#             */
/*   Updated: 2025/02/18 14:43:59 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_string(t_vars *vars, char *var_name)
{
	char	*value;

	if (ft_strlen(var_name) == 0)
		value = ft_strdup("$");
	else
		value = getenv_value(vars, var_name);
	if (value)
		return (value);
	else
		return (ft_strdup(""));
}

char	*getenv_value(t_vars *vars, char *key)
{
	t_list	*env;

	if (key == NULL)
		return (NULL);
	else if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(vars->exit_code));
	env = vars->env;
	while (env)
	{
		if (strcmp(((char **)env->content)[0], key) == 0)
			return (ft_strdup(((char **)(env->content))[1]));
		env = env->next;
	}
	return (NULL);
}
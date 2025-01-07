/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:09:56 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/07 21:11:41 by asene            ###   ########.fr       */
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
		((char **)e->content)[1] = ft_substr(pos +1, 0, ft_strlen(pos +1));
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

void	set_env(t_vars *vars, char *key, char *value)
{
	t_list	*env;
	char	**content;

	if (value == NULL)
		value = "";
	env = vars->env;
	while (env)
	{
		content = env->content;
		if (ft_strcmp(content[0], key) == 0)
		{
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

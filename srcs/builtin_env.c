/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 21:34:32 by asene             #+#    #+#             */
/*   Updated: 2025/01/22 15:15:27 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_export(char **key_value)
{
	int	i;

	if (!ft_isalpha(key_value[0][0]) && key_value[0][0] != '_')
		return (false);
	i = 0;
	while (key_value[0][++i])
		if (!ft_isalnum(key_value[0][i]) && key_value[0][i] != '_')
			return (false);
	return (true);
}

char	**parse_export_arg(char *arg)
{
	char	*equal;
	char	**key_value;

	equal = ft_strchr(arg, '=');
	if (equal)
		key_value = ft_calloc(3, sizeof(char *));
	else
		key_value = ft_calloc(2, sizeof(char *));
	if (!equal)
		key_value[0] = ft_strdup(arg);
	else
	{
		key_value[0] = ft_substr(arg, 0, equal - arg);
		key_value[1] = ft_strdup(equal + 1);
	}
	return (key_value);
}

int	ft_export(t_vars *vars, t_exec *data)
{
	int		i;
	char	**key_value;
	int		exit_code;

	if (data->argc == 1)
		return (ft_env(vars, data));
	i = 1;
	exit_code = 0;
	while (i < data->argc)
	{
		key_value = parse_export_arg(data->args[i]);
		if (!is_valid_export(key_value))
		{
			ft_fprintf(2, "export: '%s': not a valid identifier\n",
				data->args[i]);
			exit_code = 1;
		}
		else
			set_env(vars, key_value[0], key_value[1]);
		free_split(key_value);
		i++;
	}
	return (exit_code);
}

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

int	ft_unset(t_vars *vars, t_exec *data)
{
	int		i;

	i = 1;
	while (i < data->argc)
		unset_env(vars, data->args[i++]);
	return (0);
}

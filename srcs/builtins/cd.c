/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 23:34:33 by rsebasti          #+#    #+#             */
/*   Updated: 2025/02/18 14:22:02 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	get_dest(t_vars *vars, t_exec *data, char **dest)
{
	if (data->argc == 1 || ft_strcmp(data->args[1], "~") == 0)
	{
		*dest = getenv_value(vars, "HOME");
		if (*dest == NULL)
			return (ft_fprintf(2, "cd: HOME not set\n"), true);
	}
	else if (ft_strcmp(data->args[1], "-") == 0)
	{
		*dest = getenv_value(vars, "OLDPWD");
		if (*dest == NULL)
			return (ft_fprintf(2, "cd: OLDPWD not set\n"), true);
	}
	else
		*dest = ft_strdup(data->args[1]);
	return (false);
}

int	ft_cd(t_vars *vars, t_exec *data)
{
	char		*dest;
	char		*tmp;
	struct stat	st;

	if (data->argc > 2)
		return (ft_fprintf(2, "cd: too many arguments\n"), 1);
	if (get_dest(vars, data, &dest) == 1)
		return (FAILURE);
	if (ft_strlen(dest) == 0)
		return (free(dest), SUCCESS);
	if (stat(dest, &st) != 0)
		return (ft_fprintf(2, "cd: %s: No such file or directory\n", dest),
			free(dest), FAILURE);
	if (!S_ISDIR(st.st_mode))
		return (ft_fprintf(2, "cd: %s: not a directory\n", dest),
			free(dest), FAILURE);
	tmp = getenv_value(vars, "PWD");
	set_env(vars, "OLDPWD", tmp);
	free(tmp);
	chdir(dest);
	free(dest);
	tmp = getcwd(NULL, 0);
	set_env(vars, "PWD", tmp);
	free(tmp);
	return (SUCCESS);
}

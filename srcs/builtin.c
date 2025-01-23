/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 23:34:33 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/23 10:42:52 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dest_for_cd(t_vars *vars, t_exec *data, char **dest)
{
	if (data->argc == 1 || ft_strcmp(data->args[1], "~") == 0)
	{
		*dest = getenv_value(vars, "HOME");
		if (*dest == NULL)
			return (ft_fprintf(2, "cd: HOME not set\n"), 1);
	}
	else if (ft_strcmp(data->args[1], "-") == 0)
	{
		*dest = getenv_value(vars, "OLDPWD");
		if (*dest == NULL)
			return (ft_fprintf(2, "cd: OLDPWD not set\n"), 1);
	}
	else
		*dest = ft_strdup(data->args[1]);
	return (0);
}

int	ft_cd(t_vars *vars, t_exec *data)
{
	char		*dest;
	char		*tmp;
	struct stat	st;

	if (data->argc > 2)
		return (ft_fprintf(2, "cd: too many arguments\n"), 1);
	if (dest_for_cd(vars, data, &dest) == 1)
		return (FAILURE);
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

int	ft_echo(t_vars *vars, t_exec *data)
{
	int		i;
	int		new_line;

	(void)vars;
	i = 1;
	new_line = 1;
	while (i < data->argc)
	{
		if (ft_strcmp(data->args[i], "-n"))
			break ;
		new_line = 0;
		i++;
	}
	while (i < data->argc)
	{
		ft_putstr_fd(data->args[i++], data->fd_out);
		if (i < data->argc)
			ft_putchar_fd(' ', data->fd_out);
	}
	if (new_line)
		ft_putchar_fd('\n', data->fd_out);
	return (SUCCESS);
}

int	ft_exit(t_vars *vars, t_exec *data)
{
	int	exit_code;

	exit_code = vars->exit_code;
	if (data->argc == 2)
	{
		if (!parse_exit_code(data->args[1], &exit_code))
			ft_fprintf(2, "exit: %s: numeric argument required\n",
				data->args[1]);
	}
	else if (data->argc > 2)
	{
		ft_fprintf(2, "exit: too many arguments\n");
		exit_code = FAILURE;
	}
	free_exec(vars->exec_data);
	clean_exit(vars, exit_code);
	return (exit_code % 256);
}

int	ft_pwd(t_vars *vars, t_exec *data)
{
	char	*pwd;

	(void)vars;
	(void)data;
	pwd = getcwd(NULL, 0);
	ft_fprintf(data->fd_out, "%s\n", pwd);
	free(pwd);
	return (SUCCESS);
}

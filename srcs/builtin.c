/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 23:34:33 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/09 15:11:36 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_vars *vars, t_exec_data data)
{
	char		*dest;
	struct stat	st;

	if (data.argc > 2)
		return (ft_fprintf(2, "cd: too many arguments"), (void)0);
	if (data.argc == 1 || ft_strcmp(data.args[1], "~") == 0)
	{
		dest = getenv_value(vars, "HOME");
		if (dest== NULL)
			return (ft_fprintf(2, "cd: HOME not set\n"), (void)0);
	}
	else
		dest = data.args[1];
	if (stat(dest, &st) != 0)
		return (ft_fprintf(2, "cd: %s: No such file or directory\n", dest),
			(void)0);
	if (S_ISDIR(st.st_mode))
	{
		set_env(vars, "OLDPWD", getcwd(NULL, 0));
		chdir(dest);
		set_env(vars, "PWD", getcwd(NULL, 0));
	}
	else
		return (ft_fprintf(2, "cd: %s: not a directory\n", dest), (void)0);
}

void	ft_echo(t_vars *vars, t_exec_data data)
{
	int	i;

	(void)vars;
	i = 1;
	while (i < data.argc)
	{
		ft_putstr_fd(data.args[i], 1);
		if (++i < data.argc)
			ft_putchar_fd(' ', 1);
	}
	ft_putchar_fd('\n', 1);
	return ;
}

void	ft_exit(t_vars *vars, t_exec_data data)
{
	unsigned char	exit_code;

	exit_code = 0;
	if (data.argc == 2)
		exit_code = ft_atoi(data.args[1]);
	else if (data.argc > 2)
	{
		ft_fprintf(2, "exit: too many arguments\n");
		return ;
	}
	ft_lstclear(&vars->env, (void (*)(void *))free_split);
	free(vars->prompt);
	clear_token_list(&(vars->token_list));
	free_split(data.args);
	rl_clear_history();
	exit(exit_code);
}

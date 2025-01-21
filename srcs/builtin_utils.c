/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 21:36:48 by asene             #+#    #+#             */
/*   Updated: 2025/01/21 23:39:20 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int	(*get_builtin(char *cmd))(t_vars *vars, t_exec *data)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd);
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit);
	else if (ft_strcmp(cmd, "env") == 0)
		return (ft_env);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset);
	return (NULL);
}

int	is_builtin(char *cmd)
{
	return (!!(get_builtin(cmd)));
}

int	exec_builtin(t_vars *vars, t_exec *data)
{
	int		(*builtin)(t_vars *, t_exec *);
	int		exit_code;

	builtin = get_builtin(data->args[0]);
	if (!builtin)
		return (-1);
	if (dup2(data->fd_in, 0) != 0)
		close(data->fd_in);
	if (dup2(data->fd_out, 1) != 1)
		close(data->fd_out);
	exit_code = builtin(vars, data);
	if (data->pipe || data->prev)
	{
		free_exec(vars->exec_data);
		clean_exit(vars, exit_code);
	}
	return (exit_code);
}

bool	parse_exit_code(char *str, int *dest)
{
	long	nb;
	int		sign;

	nb = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	if (!*str)
		return (*dest = 2, false);
	while (*str)
	{
		if (! ft_isdigit(*str) || nb > (LONG_MAX - (*str - '0')) / 10)
			return (*dest = 2, false);
		nb = nb * 10 + *str++ - '0';
	}
	*dest = nb * sign;
	while (*dest < 0)
		*dest += 256;
	return (true);
}

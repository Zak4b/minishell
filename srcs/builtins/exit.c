/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:03:02 by asene             #+#    #+#             */
/*   Updated: 2025/02/18 14:22:22 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static bool	parse_exit_code(char *str, int *dest)
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

int	ft_exit(t_vars *vars, t_exec *data)
{
	int	exit_code;

	exit_code = vars->exit_code;
	if (data->fd_out != 1)
		close(data->fd_out);
	if (data->argc > 1 && !parse_exit_code(data->args[1], &exit_code))
	{
		ft_fprintf(2, "exit: %s: numeric argument required\n",
			data->args[1]);
		exit_code = FAILURE;
	}
	else if (data->argc > 2)
	{
		ft_fprintf(2, "exit: too many arguments\n");
		exit_code = FAILURE;
	}
	free_exec(vars->exec_data);
	ft_printf("exit\n");
	clean_exit(vars, exit_code);
	return (exit_code % 256);
}

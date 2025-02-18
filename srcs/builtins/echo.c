/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:02:04 by asene             #+#    #+#             */
/*   Updated: 2025/02/18 14:22:07 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_echo_option(char *option)
{
	int	len;
	int	i;

	if (ft_strncmp(option, "-n", 2) == 0)
	{
		len = ft_strlen(option);
		if (len != 2)
		{
			i = 2;
			while (i < len)
			{
				if (option[i] != 'n')
					return (1);
				i++;
			}
		}
		return (false);
	}
	return (true);
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
		if (is_echo_option(data->args[i]))
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

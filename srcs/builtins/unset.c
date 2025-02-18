/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:00:57 by asene             #+#    #+#             */
/*   Updated: 2025/02/18 14:01:05 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_vars *vars, t_exec *data)
{
	int		i;

	i = 1;
	while (i < data->argc)
		unset_env(vars, data->args[i++]);
	return (0);
}
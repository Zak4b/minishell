/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:03:35 by asene             #+#    #+#             */
/*   Updated: 2025/02/18 14:03:43 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
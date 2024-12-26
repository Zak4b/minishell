/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 23:34:33 by rsebasti          #+#    #+#             */
/*   Updated: 2024/12/26 10:06:40 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	select_builtin(char *builtin, t_list *tokens)
{
	if (ft_strncmp(builtin, "cd", 3) == 0)
		ft_cd();
	if (ft_strncmp(builtin, "export", 7) == 0)
		ft_export();
	if (ft_strncmp(builtin, "pwd", 4) == 0)
		ft_pwd();
	if (ft_strncmp(builtin, "echo", 5) == 0)
		ft_echo();
	if (ft_strncmp(builtin, "exit", 5) == 0)
		ft_exit();
	if (ft_strncmp(builtin, "env", 4) == 0)
		ft_env();
	if (ft_strncmp(builtin, "unset", 6) == 0)
		ft_unset();
}

void	ft_cd(void)
{
	return ;
}

void	ft_export(void)
{
	return ;
}

void	ft_pwd(void)
{
	return ;
}

void	ft_echo(void)
{
	return ;
}

void	ft_exit(t_list *tokens)
{
	(void) tokens;
	return ;
}

void	ft_env(void)
{
	return ;
}

void	ft_unset(void)
{
	return ;
}


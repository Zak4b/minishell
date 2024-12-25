/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 23:34:33 by rsebasti          #+#    #+#             */
/*   Updated: 2024/12/25 23:46:49 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	select_builtin(char *token)
{
	if (ft_strncmp(token, "cd", 3) == 0)
		ft_cd();
	if (ft_strncmp(token, "export", 7) == 0)
		ft_export();
	if (ft_strncmp(token, "pwd", 4) == 0)
		ft_pwd();
	if (ft_strncmp(token, "echo", 5) == 0)
		ft_echo();
	if (ft_strncmp(token, "exit", 5) == 0)
		ft_exit();
	if (ft_strncmp(token, "env", 4) == 0)
		ft_env();
	if (ft_strncmp(token, "unset", 6) == 0)
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

void	ft_exit(void)
{
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


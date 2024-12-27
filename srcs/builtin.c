/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 23:34:33 by rsebasti          #+#    #+#             */
/*   Updated: 2024/12/27 14:14:42 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_vars *vars)
{
	(void)vars;
	return ;
}

void	ft_export(t_vars *vars)
{
	(void)vars;
	return ;
}

void	ft_pwd(t_vars *vars)
{
	(void)vars;
	return ;
}

void	ft_echo(t_vars *vars)
{
	(void)vars;
	return ;
}

void	ft_exit(t_vars *vars)
{
	unsigned char	exit_code;
	//t_token	*arg;
	(void)vars;
	// if ((*tokens)->next && ((t_token *)(*tokens)->next->content)->type != TOKEN_END)
	// 	return (ft_putendl_fd("exit: too many arguments", 2));
	// rl_clear_history();
	// arg = (*tokens)->content;
	exit_code = 0;
	// if (arg->type == TOKEN_WORD)
	// 	exit_code = ft_atoi(arg->value);
	exit(exit_code);
}

void	ft_env(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->env[i])
	{
		ft_printf("%s\n",vars->env[i]);
		i++;
	}
}

void	ft_unset(t_vars *vars)
{
	(void)vars;
	return ;
}

void	select_builtin(t_vars *vars)
{
	char	*builtin;

	builtin = vars->current_token->token.value;
	if (ft_strcmp(builtin, "cd") == 0)
		ft_cd(vars);
	if (ft_strcmp(builtin, "export") == 0)
		ft_export(vars);
	if (ft_strcmp(builtin, "pwd") == 0)
		ft_pwd(vars);
	if (ft_strcmp(builtin, "echo") == 0)
		ft_echo(vars);
	if (ft_strcmp(builtin, "exit") == 0)
		ft_exit(vars);
	if (ft_strcmp(builtin, "env") == 0)
		ft_env(vars);
	if (ft_strcmp(builtin, "unset") == 0)
		ft_unset(vars);
}

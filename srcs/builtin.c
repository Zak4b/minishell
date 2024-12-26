/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 23:34:33 by rsebasti          #+#    #+#             */
/*   Updated: 2024/12/26 16:08:40 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_list **tokens)
{
	(void)tokens;
	return ;
}

void	ft_export(t_list **tokens)
{
	(void)tokens;
	return ;
}

void	ft_pwd(t_list **tokens)
{
	(void)tokens;
	return ;
}

void	ft_echo(t_list **tokens)
{
	(void)tokens;
	return ;
}

void	ft_exit(t_list **tokens)
{
	unsigned char	exit_code;
	t_token	*arg;

	if ((*tokens)->next && ((t_token *)(*tokens)->next->content)->type != TOKEN_END)
		return (ft_putendl_fd("exit: too many arguments", 2));
	rl_clear_history();
	arg = (*tokens)->content;
	exit_code = 0;
	if (arg->type == TOKEN_WORD)
		exit_code = ft_atoi(arg->value);
	exit(exit_code);
}

void	ft_env(t_list **tokens)
{
	(void)tokens;
	return ;
}

void	ft_unset(t_list **tokens)
{
	(void)tokens;
	return ;
}

void	select_builtin(char *builtin, t_list *tokens)
{
	if (ft_strcmp(builtin, "cd") == 0)
		ft_cd(&tokens);
	if (ft_strcmp(builtin, "export") == 0)
		ft_export(&tokens);
	if (ft_strcmp(builtin, "pwd") == 0)
		ft_pwd(&tokens);
	if (ft_strcmp(builtin, "echo") == 0)
		ft_echo(&tokens);
	if (ft_strcmp(builtin, "exit") == 0)
		ft_exit(&tokens);
	if (ft_strcmp(builtin, "env") == 0)
		ft_env(&tokens);
	if (ft_strcmp(builtin, "unset") == 0)
		ft_unset(&tokens);
}

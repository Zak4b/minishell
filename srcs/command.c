/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:55:01 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/07 16:55:24 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_word_type	cmd_or_file(t_vars *vars, char *token)
{
	if (ft_strcmp(token, "cd") == 0 || ft_strcmp(token, "export") == 0
		|| ft_strcmp(token, "pwd") == 0 || ft_strcmp(token, "echo") == 0
		|| ft_strcmp(token, "exit") == 0 || ft_strcmp(token, "env") == 0
		|| ft_strcmp(token, "unset") == 0)
		return (W_BUILTIN);
	if (correct_path(vars, token) == 1)
		return (W_CMD);
	if (access(token, F_OK | X_OK) == 0 && strncmp(token, "./", 2) == 0)
		return (W_EXECUTABLE);
	if (access(token, F_OK) == 0)
		return (W_FILE);
	return (W_NONE);
}

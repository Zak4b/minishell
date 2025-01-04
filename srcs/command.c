/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:55:01 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/03 14:00:37 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_word_type	cmd_or_file(char *token, char **env)
{
	if (ft_strcmp(token, "cd") == 0 || ft_strcmp(token, "export") == 0
		|| ft_strcmp(token, "pwd") == 0 || ft_strcmp(token, "echo") == 0
		|| ft_strcmp(token, "exit") == 0 || ft_strcmp(token, "env") == 0
		|| ft_strcmp(token, "unset") == 0)
		return (W_BUILTIN);
	if (correct_path(env, token) == 1)
		return (W_CMD);
	if (access(token, F_OK | X_OK) == 0 && strncmp(token, "./", 2) == 0)
		return (W_EXECUTABLE);
	if (access(token, F_OK) == 0)
		return (W_FILE);
	return (W_NONE);
}

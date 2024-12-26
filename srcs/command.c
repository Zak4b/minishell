/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:55:01 by rsebasti          #+#    #+#             */
/*   Updated: 2024/12/26 16:07:01 by asene            ###   ########.fr       */
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
	if (access(token, F_OK | X_OK) == 0)
		return (W_EXECUTABLE);
	if (access(token, F_OK) == 0)
		return (W_FILE);
	if (search_path(env, token) != NULL)
		return (W_CMD);
	return (W_NONE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:55:01 by rsebasti          #+#    #+#             */
/*   Updated: 2024/12/26 11:16:57 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_word_type	cmd_or_file(char *token, char **env)
{
	if (ft_strncmp(token, "cd", 3) == 0 || ft_strncmp(token, "export", 7) == 0
		|| ft_strncmp(token, "pwd", 4) == 0 || ft_strncmp(token, "echo", 5) == 0
		|| ft_strncmp(token, "exit", 5) == 0 || ft_strncmp(token, "env", 4) == 0
		|| ft_strncmp(token, "unset", 6) == 0)
		return (W_BUILTIN);
	if (access(token, F_OK | X_OK) == 0)
		return (W_EXECUTABLE);
	if (access(token, F_OK) == 0)
		return (W_FILE);
	if (search_path(env, token) != NULL)
		return (W_CMD);
	return (W_NONE);
}

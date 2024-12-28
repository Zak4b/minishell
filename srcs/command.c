/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:55:01 by rsebasti          #+#    #+#             */
/*   Updated: 2024/12/28 13:51:23 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exec_cmd(char *token, char **env)
{
	char	*path;

	path = search_path(env, token);
	if (path != NULL)
	{
		free(path);
		return (1);
	}
	else
		return (0);
}

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
	if (is_exec_cmd(token, env))
		return (W_CMD);
	return (W_NONE);
}

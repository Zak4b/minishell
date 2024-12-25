/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:55:01 by rsebasti          #+#    #+#             */
/*   Updated: 2024/12/25 23:32:48 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_or_file(char *token, char **env)
{
	if (ft_strncmp(token, "cd", 3) == 0 || ft_strncmp(token, "export", 7) == 0
		|| ft_strncmp(token, "pwd", 4) == 0 || ft_strncmp(token, "echo", 5) == 0
		|| ft_strncmp(token, "exit", 5) == 0 || ft_strncmp(token, "env", 4) == 0
		|| ft_strncmp(token, "unset", 6) == 0)
		return (4);
	if (access(token, F_OK | X_OK) == 0)
		return (1);
	if (access(token, F_OK) == 0)
		return (2);
	if (search_path(env, token) != NULL)
		return (3);
	return (0);
}

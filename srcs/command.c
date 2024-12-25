/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:55:01 by rsebasti          #+#    #+#             */
/*   Updated: 2024/12/25 22:49:49 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_or_file(char *token, char **env)
{
	if (access(token, F_OK | X_OK) == 0)
		return (1);
	if (access(token, F_OK) == 0)
		return (2);
	if (search_path(env, token) != NULL)
		return (3);
	return (0);
}


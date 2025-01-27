/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 21:45:51 by asene             #+#    #+#             */
/*   Updated: 2025/01/27 14:02:01 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_file_error(char *file, char **msg, int *exit_code)
{
	struct stat	st;

	if (stat(file, &st) != 0)
	{
		if (exit_code)
			*exit_code = NOT_FOUND;
		if (msg)
			*msg = "No such file or directory";
	}
	else
	{
		if (exit_code)
			*exit_code = FILE_ERROR;
		if (msg)
		{
			if (S_ISDIR(st.st_mode))
				*msg = "Is a directory";
			else
				*msg = "Permission denied";
		}
	}
}

void	file_error(char *file)
{
	char	*msg;

	get_file_error(file, &msg, NULL);
	ft_fprintf(2, "minishell: %s: %s\n", file, msg);
}

int	exec_error(t_vars *vars, t_exec *data)
{
	char		*msg;
	char		*path;
	int			error;

	error = NOT_FOUND;
	path = getenv_value(vars, "PATH");
	if (!ft_strchr(data->args[0], '/') && path && !data->path)
		msg = "command not found";
	else
		get_file_error(data->args[0], &msg, &error);
	free(path);
	ft_fprintf(2, "minishell: %s: %s\n", data->args[0], msg);
	return (error);
}

void	syntaxe_error(t_token *token)
{
	ft_fprintf(2, "minishell: syntax error near unexpected token `%s'\n",
		token_str(token));
}

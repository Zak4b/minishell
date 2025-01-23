/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 21:45:51 by asene             #+#    #+#             */
/*   Updated: 2025/01/23 13:40:11 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_error(char *input)
{
	char		*msg;
	struct stat	st;
	int			error;

	error = NOT_FOUND;
	if (ft_strchr(input, '/'))
	{
		if (stat(input, &st) != 0)
			msg = "No such file or directory";
		else
		{
			error = FILE_ERROR;
			if (S_ISDIR(st.st_mode))
				msg = "Is a directory";
			else
				msg = "Permission denied";
		}
		ft_fprintf(2, "minishell: %s: %s\n", input, msg);
	}
	else
		ft_fprintf(2, "%s: command not found\n", input);
	return (error);
}

void	file_error(char *file)
{
	char	*msg;

	if (access(file, F_OK) == 0)
		msg = "Permission denied";
	else
		msg = "No such file or directory";
	ft_fprintf(2, "minishell: %s: %s\n", file, msg);
}

void	syntaxe_error(t_token *token)
{
	ft_fprintf(2, "minishell: syntax error near unexpected token `%s'\n",
		token_str(token));
}

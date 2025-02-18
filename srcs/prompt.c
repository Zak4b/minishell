/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:56:27 by asene             #+#    #+#             */
/*   Updated: 2025/02/18 13:28:35 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_prompt(t_vars *vars)
{
	int		i;
	char	*prompt_parts[5];
	char	*pwd;
	char	*home;
	char	*prompt;

	i = 0;
	prompt_parts[i++] = "\001\e[1;32m\002minishell:\001\e[1;34m\002";
	pwd = getcwd(NULL, 0);
	home = getenv_value(vars, "HOME");
	if (pwd && home && ft_strncmp(home, pwd, ft_strlen(home)) == 0)
	{
		prompt_parts[i++] = "~";
		prompt_parts[i++] = pwd + ft_strlen(home);
	}
	else if (pwd)
		prompt_parts[i++] = pwd;
	free(home);
	prompt_parts[i++] = " > \001\e[0m\002";
	prompt = ft_strnjoin(prompt_parts, i, "");
	free(pwd);
	return (prompt);
}

char	*readline_prompt(t_vars *vars, char **dest)
{
	char	*prompt;
	char	*input;

	prompt = get_prompt(vars);
	input = readline(prompt);
	free(prompt);
	if (input && *input)
		add_history(input);
	*dest = input;
	return (input);
}

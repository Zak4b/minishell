/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:49:58 by asene             #+#    #+#             */
/*   Updated: 2025/01/21 22:29:29 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	clean_exit(t_vars *vars, int exit_code)
{
	ft_lstclear(&vars->env, (void (*)(void *))free_split);
	clear_token_list(&(vars->token_list));
	rl_clear_history();
	exit(exit_code);
}

int	count_line(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	skip_spaces(char **str)
{
	if (!ft_isspace(**str))
		return (0);
	while (**str && ft_isspace(**str))
		(*str)++;
	return (1);
}

char	*str_append(char **dest, char *next)
{
	unsigned int	new_len;
	char			*new_str;

	new_len = ft_strlen(*dest) + ft_strlen(next) + 1;
	new_str = ft_calloc(new_len, sizeof(char));
	ft_strlcat(new_str, *dest, new_len);
	ft_strlcat(new_str, next, new_len);
	free(*dest);
	*dest = new_str;
	return (new_str);
}

// return exit code from waitpid status
int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

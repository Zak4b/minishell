/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:51:51 by asene             #+#    #+#             */
/*   Updated: 2025/01/16 16:24:39 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>	

volatile sig_atomic_t	g_nal = 0;

void	init_shell(t_vars *vars, char **env)
{
	vars->token_list = NULL;
	vars->exit_code = 0;
	setup_signal(vars);
	parse_env(env, vars);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_vars	vars;

	if (argc > 1)
		return (ft_fprintf(2, "Usage: %s\n", argv[0]), 1);
	init_shell(&vars, env);
	while (1)
	{
		if (g_nal == SIGINT)
			ft_putchar_fd('\n', 1);
		if (g_nal == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 1);
		g_nal = 0;
		if (readline_prompt(&vars, &input) == NULL)
			return (free(input), clean_exit(&vars, 0), 0);
		vars.token_list = tokenize(input);
		vars.exit_code = execute(&vars);
		clear_token_list(&(vars.token_list));
		free(input);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:51:51 by asene             #+#    #+#             */
/*   Updated: 2024/12/30 17:28:18 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_nal = 0;

void	analyze_token(t_token *token, char **env)
{
	if (cmd_or_file(token->value, env) == W_CMD)
		printf("'%s' est une commande valide.\n", token->value);
	else if (cmd_or_file(token->value, env) == W_FILE)
		printf("'%s' est un fichier existant.\n", token->value);
	else if (cmd_or_file(token->value, env) == W_EXECUTABLE)
		printf("'%s' est un fichier executable.\n", token->value);
	else if (cmd_or_file(token->value, env) == W_BUILTIN)
		printf("'%s' est une commande builtin.\n", token->value);
	else
		printf("'%s' est une commande invalide.\n", token->value);
}

void	print_tokens(t_tokenlist *list, char **env)
{
	while (list)
	{
		if (list->token.type == TOKEN_WORD)
			analyze_token(&list->token, env);
		else
			ft_printf("Type: %d, %s\n", list->token.type, list->token.value);
		list = list->next;
	}
}

void	init_shell(t_vars *vars, char **env)
{
	vars->token_list = NULL;
	vars->current_token = NULL;
	setup_signal();
	parse_env(env, vars);
}

char	*set_prompt(t_vars *vars)
{
	char	*prompt;
	char	*pwd;
	char	*home;
	int		home_len;

	pwd = getenv_value(vars->env, "PWD");
	home = getenv_value(vars->env, "HOME");
	home_len = (int) ft_strlen(home);
	if (ft_strncmp(home, pwd, home_len) == 0)
		prompt = ft_strdoublejoin("minishell:~",
				pwd + (ft_strlen(pwd) + 1 - home_len), "> ");
	else
		prompt = ft_strdoublejoin("minishell:", pwd, "> ");
	vars->prompt = prompt;
	return (prompt);
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
		input = readline(set_prompt(&vars));
		add_history(input);
		if (input == NULL)
			return (free(input), free_split(vars.env), free(vars.prompt), 0);
		vars.token_list = tokenize(input);
		execute(&vars);
		clear_token_list(&(vars.token_list));
		free(input);
		free(vars.prompt);
	}
	return (0);
}

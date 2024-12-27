/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:51:51 by asene             #+#    #+#             */
/*   Updated: 2024/12/27 13:53:13 by asene            ###   ########.fr       */
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

void	init_shell(t_vars *vars)
{
	vars->token_list = NULL;
	vars->current_token = NULL;
	setup_sign();
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_vars	vars;

	if (argc > 1)
		return (ft_fprintf(2, "Usage: %s\n", argv[0]), 1);
	init_shell(&vars);
	while (1)
	{
		input = readline("minishell> ");
		add_history(input);
		if (input == NULL)
			return (free(input), 0);
		vars.token_list = tokenize(input);
		print_tokens(vars.token_list , env);
		execute(&vars);
		clear_token_list(vars.token_list);
		free(input);
	}
	return (0);
}

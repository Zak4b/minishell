/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:51:51 by asene             #+#    #+#             */
/*   Updated: 2024/12/26 13:52:42 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_nal = 0;

void	analyze_token(t_token *token, char **env)
{
	if (cmd_or_file(token->value, env) == 3)
		printf("'%s' est une commande valide.\n", token->value);
	else if (cmd_or_file(token->value, env) == 2)
		printf("'%s' est un fichier existant.\n", token->value);
	else if (cmd_or_file(token->value, env) == 1)
		printf("'%s' est un fichier executable.\n", token->value);
	else if (cmd_or_file(token->value, env) == 4)
		printf("'%s' est une commande builtin.\n", token->value);
	else
		printf("'%s' est une commande invalide.\n", token->value);
}

void	print_tokens(t_list *list, char **env)
{
	t_token	*t;

	while (list)
	{
		t = list->content;
		if (t->type == TOKEN_WORD)
			analyze_token(t, env);
		else
			ft_printf("Type: %d, %s\n", t->type, t->value);
		list = list->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_list	*tokens;

	if (argc > 1)
		return (ft_fprintf(2, "Usage: %s\n", argv[0]), 1);
	setup_sign();
	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL || ft_strncmp(input, "exit", 5) == 0)
			return (free(input), 0);
		tokens = tokenize(input);
		print_tokens(tokens, env);
		ft_lstclear(&tokens, (void (*)(void *))free_token);
		free(input);
	}
	return (0);
}

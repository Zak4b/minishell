/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:51:51 by asene             #+#    #+#             */
/*   Updated: 2024/12/29 14:02:44 by rsebasti         ###   ########.fr       */
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
	setup_sign();
	env_parser(env, vars);
}

char	*set_prompt(t_vars *vars)
{
	char	*prompt;
	char	**arg;
	int		size;
	int		homesize;

	arg = malloc(sizeof(char *) * 3);
	if (arg == NULL)
		return (NULL);
	arg[1] = clean_word(vars->env, "PWD");
	size = (int) ft_strlen(arg[1]);
	arg[0] = clean_word(vars->env, "HOME");
	homesize = (int) ft_strlen(arg[0]);
	if (strncmp(arg[0], arg[1], homesize) == 0)
		prompt = ft_strdoublejoin("minishell:~",
				arg[1] + (size - homesize), "> ");
	else
	{
		arg[0] = "minishell:";
		arg[2] = "> ";
		prompt = ft_strdoublejoin(arg[0], arg[1], arg[2]);
	}
	free(arg);
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

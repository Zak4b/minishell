/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:51:51 by asene             #+#    #+#             */
/*   Updated: 2025/01/09 11:23:08 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_nal = 0;

void	analyze_token(t_vars *vars, t_token *token)
{
	t_word_type	type;

	type = cmd_or_file(vars, token->value);
	if (type == W_CMD)
		printf("'%s' est une commande valide.\n", token->value);
	else if (type == W_FILE)
		printf("'%s' est un fichier existant.\n", token->value);
	else if (type == W_EXECUTABLE)
		printf("'%s' est un fichier executable.\n", token->value);
	else if (type == W_BUILTIN)
		printf("'%s' est une commande builtin.\n", token->value);
	else
		printf("'%s' est une commande invalide.\n", token->value);
}

void	print_tokens(t_vars *vars, t_tokenlist *list)
{
	while (list)
	{
		if (list->token.type == TOKEN_WORD)
			analyze_token(vars, &list->token);
		else
			ft_printf("Type: %d, %s\n", list->token.type, list->token.value);
		list = list->next;
	}
}

void	init_shell(t_vars *vars, char **env)
{
	vars->token_list = NULL;
	vars->current_token = NULL;
	setup_signal(vars);
	parse_env(env, vars);
}

char	*set_prompt(t_vars *vars)
{
	int		i;
	char	*prompt[5];
	char	*pwd;
	char	*home;

	i = 0;
	prompt[i++] = "minishell:";
	pwd = getcwd(NULL, 0);
	home = getenv_value(vars, "HOME");
	if (pwd && home && ft_strncmp(home, pwd, ft_strlen(home)) == 0)
	{
		prompt[i++] = "~";
		prompt[i++] = pwd + ft_strlen(home);
	}
	else if (pwd)
		prompt[i++] = pwd;
	prompt[i++] = " > ";
	vars->prompt = ft_strnjoin(prompt, i, "");
	return (free(pwd), vars->prompt);
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
		{
			ft_printf("\n");
			g_nal = 0;
		}
		if (g_nal == SIGQUIT)
		{
			ft_printf("Quit (core dumped)\n");
			g_nal = 0;
		}

		input = readline(set_prompt(&vars));
		add_history(input);
		if (input == NULL)
			return (free(input), ft_lstclear(&vars.env, (void (*)(void *))free_split), free(vars.prompt), 0);
		vars.token_list = tokenize(input);
		execute(&vars);
		clear_token_list(&(vars.token_list));
		free(input);
		free(vars.prompt);
	}
	return (0);
}

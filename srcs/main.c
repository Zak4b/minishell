/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:51:51 by asene             #+#    #+#             */
/*   Updated: 2024/12/24 17:01:09 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_token_list	tokens;

	if (argc > 1)
		return (ft_fprintf(2, "Usage: %s\n", argv[0]), 1);
	(void)envp;
	while (1)
	{
		input = readline("Entrez une commande : ");
		if (ft_strncmp(input, "exit", 5) == 0)
			return (free(input), 0);
		tokens = tokenize(input);
		print_tokens(&tokens);
		free_tokens(&tokens);
		free(input);
	}
	return (0);
}

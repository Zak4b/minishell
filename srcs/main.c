/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:51:51 by asene             #+#    #+#             */
/*   Updated: 2024/12/25 20:29:14 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*tokens;

	if (argc > 1)
		return (ft_fprintf(2, "Usage: %s\n", argv[0]), 1);
	(void)envp;
	while (1)
	{
		input = readline("Prompt : ");
		if (ft_strncmp(input, "exit", 5) == 0)
			return (free(input), 0);
		tokens = tokenize(input);
		print_tokens(tokens);
		ft_lstclear(&tokens, (void (*)(void *))free_token);
		free(input);
	}
	return (0);
}

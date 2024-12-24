/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:46:54 by asene             #+#    #+#             */
/*   Updated: 2024/12/24 17:09:03 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_token(t_token_list *list, t_token_type type, char *value)
{
	if (list->count >= MAX_TOKENS)
	{
		ft_fprintf(2, "Erreur : trop de tokens\n");
		exit(EXIT_FAILURE);
	}
	list->tokens[list->count].type = type;
	list->tokens[list->count].value = value;
	list->count++;
}

char	*get_word_token(char **ptr)
{
	char	buffer[MAX_CMD_LEN];
	int		buf_index;

	buf_index = 0;
	while (**ptr && !is_space(**ptr) && ft_strchr("|<>", **ptr) == NULL)
	{
		buffer[buf_index++] = **ptr;
		*ptr = *ptr + 1;
	}
	buffer[buf_index] = '\0';
	return (ft_strdup(buffer));
}

t_token_list	tokenize(const char *input)
{
	t_token_list	list;
	const char		*ptr;

	ptr = input;
	list.count = 0;
	while (*ptr)
	{
		while (*ptr && is_space(*ptr))
			ptr++;
		if (*ptr == '|' && ++ptr)
			add_token(&list, TOKEN_PIPE, ft_strdup("|"));
		else if (*ptr == '>')
		{
			if (*(ptr + 1) == '>' && ++ptr)
				add_token(&list, TOKEN_APPEND, ft_strdup(">>"));
			else
				add_token(&list, TOKEN_REDIRECT_OUT, ft_strdup(">"));
			ptr++;
		}
		else if (*ptr == '<' && ++ptr)
			add_token(&list, TOKEN_REDIRECT_IN, ft_strdup("<"));
		else
			add_token(&list, TOKEN_WORD, get_word_token((char **)&ptr));
	}
	return (add_token(&list, TOKEN_END, ft_strdup("END")), list);
}

void	print_tokens(t_token_list *list)
{
	int		i;
	t_token	*t;

	i = 0;
	while (i < list->count)
	{
		t = &list->tokens[i];
		ft_printf("Token[%d]: Type=%d, %s\n", i, t->type, t->value);
		i++;
	}
}

void	free_tokens(t_token_list *list)
{
	int	i;

	i = 0;
	while (i < list->count)
		free(list->tokens[i++].value);
}

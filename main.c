/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:51:51 by asene             #+#    #+#             */
/*   Updated: 2024/12/24 15:38:08 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1)
		return (ft_fprintf(2, "Usage: %s\n", argv[0]), 1);
	(void)envp;
	while (1)
	{
		readline("Prompt");
	}
}


void add_token(t_token_list *list, t_token_type type, const char *value) {
    if (list->count >= MAX_TOKENS) {
        fprintf(2, "Erreur : trop de tokens\n");
        exit(EXIT_FAILURE);
    }
    list->tokens[list->count].type = type;
    list->tokens[list->count].value = strdup(value);
    list->count++;
}
t_token_list tokenize(const char *input) {
    t_token_list list = {.count = 0};
    const char *ptr = input;
    char buffer[MAX_CMD_LEN];
    int buf_index = 0;

    while (*ptr) {
        if (isspace(*ptr)) {
            ptr++;  // Ignorer les espaces
            continue;
        }

        if (*ptr == '|') {
            add_token(&list, TOKEN_PIPE, "|");
            ptr++;
        } else if (*ptr == '>') {
            if (*(ptr + 1) == '>') {
                add_token(&list, TOKEN_APPEND, ">>");
                ptr += 2;
            } else {
                add_token(&list, TOKEN_REDIRECT_OUT, ">");
                ptr++;
            }
        } else if (*ptr == '<') {
            add_token(&list, TOKEN_REDIRECT_IN, "<");
            ptr++;
        } else {
            // Lire un mot (commande ou argument)
            buf_index = 0;
            while (*ptr && !isspace(*ptr) && *ptr != '|' && *ptr != '>' && *ptr != '<') {
                buffer[buf_index++] = *ptr++;
            }
            buffer[buf_index] = '\0';
            add_token(&list, TOKEN_WORD, buffer);
        }
    }

    add_token(&list, TOKEN_END, "END");
    return list;
}

// Fonction pour afficher les tokens
void print_tokens(const t_token_list *list) {
    for (int i = 0; i < list->count; i++) {
        printf("Token[%d]: Type=%d, Value=%s\n", i, list->tokens[i].type, list->tokens[i].value);
    }
}

// Libérer les tokens
void free_tokens(t_token_list *list) {
    for (int i = 0; i < list->count; i++) {
        free(list->tokens[i].value);
    }
}

int main() {
    char input[MAX_CMD_LEN];

    printf("Entrez une commande : ");
    if (fgets(input, sizeof(input), 1) == NULL) {
        perror("Erreur de lecture");
        return EXIT_FAILURE;
    }

    // Supprimer le saut de ligne
    input[strcspn(input, "\n")] = 0;

    t_token_list tokens = tokenize(input);
    print_tokens(&tokens);
    free_tokens(&tokens);

    return 0;
}

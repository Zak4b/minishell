/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 09:30:16 by rsebasti          #+#    #+#             */
/*   Updated: 2024/12/26 10:39:16 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signal.h"

void	handle_signal(int sign)
{
	if (sign == SIGINT)
		ft_printf("\nminishell> ");
	if (sign == SIGQUIT)
		ft_printf("SIQUIT RECU \n");
}
int	setup_sign(void)
{
	if (signal(SIGINT, handle_signal) == SIG_ERR)
		return (perror("Erreur lors de la configuration de SIGINT"), 1);
	if (signal(SIGQUIT, handle_signal) == SIG_ERR)
		return (perror("Erreur lors de la configuration de SIGQUIT"), 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 09:30:16 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/08 14:51:37 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sign, siginfo_t *info, void *context)
{
	(void) context;
	g_nal = sign;
	if (sign == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sign == SIGQUIT)
	{
		kill(info->si_pid, SIGQUIT);
		g_nal = 0;
		ft_fprintf(2, "Quit (core dumped)\n");
	}

}

int	setup_signal(t_vars *vars)
{
	struct sigaction sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1) {
		perror("sigaction");
		return (1);
	}
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1) {
		perror("sigaction");
		return (1);
	}
	vars->sa = sa;
	return (0);
}

int	start_signal(t_vars *vars)
{
	vars->sa.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &vars->sa, NULL) == -1) {
		perror("sigaction");
		return 1;
	}
	if (sigaction(SIGQUIT, &vars->sa, NULL) == -1) {
		perror("sigaction");
		return 1;
	}
	return (0);
}

int	stop_signal(t_vars *vars)
{
	vars->sa.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &vars->sa, NULL) == -1) {
		perror("sigaction");
		return 1;
	}
	if (sigaction(SIGQUIT, &vars->sa, NULL) == -1) {
		perror("sigaction");
		return 1;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:34:03 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/11 12:02:46 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(int sign)
{
	if (sign == SIGINT)
	{
		g_nal = sign;
		rl_done = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

int	signal_heredoc(t_vars *vars)
{
	vars->sa.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &vars->sa, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}
	vars->sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &vars->sa, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}
	return (1);
}

void	heredoc_child(char *delimiter)
{
	char	*line;
	int		fd;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0 || g_nal == SIGINT)
		{
			free(line);
			break ;
		}
		ft_fprintf(fd, "%s\n", line);
		free(line);
	}
	close(fd);
	exit(0);
}

char	*heredoc(char *delimiter, t_vars *vars)
{
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid == 0 && signal_heredoc(vars))
		heredoc_child(delimiter);
	else
	{
		waitpid(pid, 0, 0);
		if (g_nal == SIGINT)
		{
			fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			close(fd);
		}

	}
	return (".heredoc");
}


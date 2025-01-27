/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:34:03 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/27 15:41:28 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty_event(void)
{
	return (0);
}

void	handle_herdoc(int sig)
{
	g_nal = sig;
	if (sig == SIGINT)
		rl_done = 1;
}

int	signal_heredoc(t_vars *vars)
{
	vars->sa.sa_handler = handle_herdoc;
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

void	heredoc_child(t_vars *vars, char *name, char *delimiter, bool eval_vars)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0 || g_nal == SIGINT)
		{
			free(line);
			break ;
		}
		if (eval_vars)
		{
			tmp = replace_vars(vars, line);
			free(line);
			line = tmp;
		}
		ft_fprintf(fd, "%s\n", line);
		free(line);
	}
	close(fd);
}

void	heredoc_killer(int nbheredoc)
{
	int		i;
	char	*name;
	char	*number;

	if (nbheredoc == 0)
		return ;
	i = 0;
	while (i <= nbheredoc)
	{
		number = ft_itoa(i);
		name = ft_strjoin(".heredoc", number);
		unlink(name);
		i++;
		free(name);
		free(number);
	}
}

int	heredoc(t_vars *vars, char *delimiter, bool eval_vars)
{
	int		fd;
	char	*name;
	char	*number;

	number = ft_itoa(vars->nbheredoc);
	name = ft_strjoin(".heredoc", number);
	free(number);
	rl_event_hook = empty_event;
	signal_heredoc(vars);
	heredoc_child(vars, name, delimiter, eval_vars);
	fd = -1;
	if (g_nal != SIGINT)
	{
		fd = open(name, O_RDONLY, 0644);
		vars->nbheredoc++;
	}
	else
		unlink(name);
	rl_event_hook = NULL;
	return (free(name), fd);
}

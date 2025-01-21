/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:34:03 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/21 16:26:40 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	heredoc_child(char *delimiter, char *name)
{
	char	*line;
	int		fd;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

void	heredoc_killer(int nbheredoc)
{
	int		i;
	char	*name;

	if (nbheredoc == 0)
		return ;
	i = 0;
	while (i <= nbheredoc)
	{
		name = ft_strjoin(".heredoc", ft_itoa(i));
		unlink(name);
		i++;
		free(name);
	}
}

int	heredoc(char *delimiter, t_vars *vars)
{
	int		fd;
	pid_t	pid;
	char	*name;
	char	*number;

	number = ft_itoa(vars->nbheredoc);
	name = ft_strjoin(".heredoc", number);
	free(number);
	pid = fork();
	if (pid == 0 && signal_heredoc(vars))
		heredoc_child(delimiter, name);
	else
	{
		waitpid(pid, 0, 0);
		if (g_nal == SIGINT)
		{
			fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			close(fd);
		}
	}
	fd = open(name, O_RDONLY, 0644);
	free(name);
	vars->nbheredoc = vars->nbheredoc + 1;
	return (fd);
}

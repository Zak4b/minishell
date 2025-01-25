/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:34:03 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/25 14:24:26 by asene            ###   ########.fr       */
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

void	heredoc_child(t_vars *vars, char *name, char *delimiter, bool eval_vars)
{
	int		fd;
	char	*line;

	free_exec(vars->exec_data);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(name);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0 || g_nal == SIGINT)
		{
			free(line);
			break ;
		}
		if (eval_vars)
			ftf_print_var(fd, line, vars);
		else
			ft_fprintf(fd, "%s\n", line);
		free(line);
	}
	free(delimiter);
	close(fd);
	clean_exit(vars, 0);
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
	pid_t	pid;
	char	*name;
	char	*number;

	number = ft_itoa(vars->nbheredoc);
	name = ft_strjoin(".heredoc", number);
	free(number);
	pid = fork();
	if (pid == 0 && signal_heredoc(vars))
		heredoc_child(vars, name, delimiter, eval_vars);
	waitpid(pid, 0, 0);
	if (g_nal != SIGINT)
	{
		fd = open(name, O_RDONLY, 0644);
		vars->nbheredoc++;
	}
	else
	{
		fd = -1;
		unlink(name);
	}
	free(name);
	return (fd);
}

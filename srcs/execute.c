/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:56:53 by asene             #+#    #+#             */
/*   Updated: 2025/01/27 15:42:26 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// execve || exit
void	exec_cmd(t_vars *vars, t_exec *data)
{
	char	**env;
	int		exit;

	if (dup2(data->fd_in, 0) != 0)
		close(data->fd_in);
	if (dup2(data->fd_out, 1) != 1)
		close(data->fd_out);
	if (data->path)
	{
		env = build_env(vars);
		execve(data->path, data->args, env);
		free_split(env);
	}
	exit = exec_error(vars, data);
	free_exec(vars->exec_data);
	clean_exit(vars, exit);
}

// Return exit code
int	run_cmd(t_vars *vars, t_exec *data, bool need_fork)
{
	int		status;
	pid_t	pid;

	if (data->fd_in == -1 || data->fd_out == -1)
	{
		if (!need_fork)
			free_exec(vars->exec_data);
		return (1);
	}
	if (is_builtin(data->args[0]))
		return (exec_builtin(vars, data));
	else
	{
		if (need_fork)
			pid = fork();
		else
			pid = 0;
		if (pid == 0)
			exec_cmd(vars, data);
		waitpid(pid, &status, 0);
		return (get_exit_code(status));
	}
}

void	child_process(t_vars *vars, t_exec *data, int *fds)
{
	int	exit_code;

	if (fds[0])
		close(fds[0]);
	exit_code = run_cmd(vars, data, false);
	clean_exit(vars, exit_code);
}

int	execute_pipeline(t_vars *vars, t_exec *data, int input_fd)
{
	pid_t	pid;
	int		fds[2];
	int		status;

	fds[0] = 0;
	if (data->pipe)
	{
		pipe(fds);
		if (isatty(data->fd_out))
			data->fd_out = fds[1];
		if (isatty(data->pipe->fd_in))
			data->pipe->fd_in = fds[0];
	}
	pid = fork();
	if (pid == 0)
		child_process(vars, data, fds);
	if (!isatty(input_fd))
		close(input_fd);
	if (data->pipe == NULL)
		return (waitpid(pid, &status, 0), status);
	close(fds[1]);
	status = execute_pipeline(vars, data->pipe, fds[0]);
	waitpid(pid, NULL, 0);
	return (status);
}

int	execute(t_vars *vars)
{
	int			exit_code;

	vars->exec_data = NULL;
	vars->nbheredoc = 0;
	stop_signal(vars);
	build_exec(vars, vars->token_list, &vars->exec_data, NULL);
	if (!vars->exec_data->args[0] || g_nal == SIGINT)
		return (start_signal(vars), g_nal = 0,free_exec(vars->exec_data)
			, vars->exit_code);
	if (vars->exec_data->pipe)
		exit_code = get_exit_code(execute_pipeline(vars, vars->exec_data, 0));
	else
		exit_code = run_cmd(vars, vars->exec_data, true);
	free_exec(vars->exec_data);
	start_signal(vars);
	heredoc_killer(vars->nbheredoc);
	return (exit_code);
}

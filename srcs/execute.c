/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:56:53 by asene             #+#    #+#             */
/*   Updated: 2025/01/16 14:09:16 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_exec(t_exec_data *data)
{
	if (data->path)
		free(data->path);
	if (data->args)
		free_split(data->args);
	if (access(".heredoc", F_OK) == 0)
		unlink(".heredoc");
	if (data->pipe)
		free_exec(data->pipe);
	free(data);
}

void	exec_cmd(t_vars *vars, t_exec_data *data)
{
	char	**env;

	if (dup2(data->fd_in, 0) != 0)
		close(data->fd_in);
	if (dup2(data->fd_out, 1) != 1)
		close(data->fd_out);
	if (!data->path)
	{
		ft_fprintf(2, "%s: command not found\n", data->args[0]);
		clean_exit(vars, 1);
	}
	env = build_env(vars);
	execve(data->path, data->args, env);
	free_split(env);
	clean_exit(vars, 1);
}

void	child_process(t_vars *vars, t_exec_data *data, int *fds)
{
	close(fds[0]);
	if (is_builtin(data->args[0]))
		exec_builtin(vars, *data);
	else if (data->path)
		exec_cmd(vars, data);
	free_exec(data);
	exit(15); // TODO
}

int	execute_pipeline(t_vars *vars, t_exec_data *data, int input_fd)
{
	pid_t	pid;
	int		fds[2];
	int		status;

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

int	run_cmd(t_vars *vars, t_exec_data *data)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_cmd(vars, data);
	return (waitpid(pid, &status, 0), status);
}

int	execute(t_vars *vars)
{
	int			status;
	t_exec_data	*data;

	stop_signal(vars);
	data = NULL;
	build_exec(vars, vars->token_list, &data);
	if(!data->args[0])
		return (start_signal(vars), 1);
	if (data->pipe)
		status = execute_pipeline(vars, data, STDIN_FILENO);
	else if (is_builtin(data->args[0]))
		status = exec_builtin(vars, *data);
	else
		status = run_cmd(vars, data);
	start_signal(vars);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (1);
}

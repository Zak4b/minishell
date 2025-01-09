/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:56:53 by asene             #+#    #+#             */
/*   Updated: 2025/01/09 16:06:57 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	free_exec(t_exec_data data)
{
	if (data.path)
		free(data.path);
	if (data.args)
		free_split(data.args);
	if (data.pipe)
		free(data.pipe);
	return (0);
}

pid_t	exec_cmd(t_vars *vars, t_exec_data data)
{
	pid_t	pid;
	char	**env;

	(void)vars;
	pid = fork();
	if (pid == -1)
		perror("Error on fork ");
	else if (pid == 0)
	{
		if (dup2(data.fd_in, 0) != 0)
			close(data.fd_in);
		if (dup2(data.fd_out, 1) != 1)
			close(data.fd_out);
		env = build_env(vars);
		execve(data.path, data.args, env);
		free_split(env);
	}
	return (pid);
}

int	handle_pipe(t_vars *vars, t_exec_data *data, int *fd_in, int *fd_out)
{
	int	pipe_fd[2];

	if (vars->current_token->token.type == TOKEN_PIPE)
	{
		vars->current_token = vars->current_token->next;
		if (pipe(pipe_fd) == 0)
		{
			*fd_in = pipe_fd[0];
			*fd_out = pipe_fd[1];
			data->pipe = pipe_fd;
			if (data->fd_out == 1)
				data->fd_out = *fd_out;
			return (1);
		}
	}
	*fd_in = 0;
	*fd_out = 1;
	return (0);
}

int	end_exec(pid_t pid, t_vars *vars)
{
	int		status;
	int		exit_status;

	if (waitpid(pid, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
	}
	while (wait(&(int){0}) > 0)
		;
	start_signal(vars);
	return (exit_status);
}

int	execute(t_vars *vars)
{
	int			use_pipe;
	int			fd[2];
	pid_t		pid;
	t_exec_data	data;


	vars->current_token = vars->token_list;
	use_pipe = 0;
	stop_signal(vars);
	while (vars->current_token->token.type != TOKEN_END)
	{
		data = build_exec(vars);
		if (use_pipe)
			data.fd_in = fd[0];
		use_pipe = handle_pipe(vars, &data, &fd[0], &fd[1]);
		if (isatty(data.fd_in))
			data.fd_in = fd[0];
		if (isatty(data.fd_out))
			data.fd_out = fd[1];
		if (is_builtin(data.args[0]))
			exec_builtin(vars, data);
		else if (data.path)
			pid = exec_cmd(vars, data);
		else if (data.args[0])
			ft_fprintf(2, "%s: command not found\n", data.args[0]);
		free_exec(data);
	}
	return (end_exec(pid, vars));
}

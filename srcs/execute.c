/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:56:53 by asene             #+#    #+#             */
/*   Updated: 2025/01/13 14:01:01 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	free_exec(t_exec_data data)
{
	if (data.path)
		free(data.path);
	if (data.args)
		free_split(data.args);
	if (access(".heredoc", F_OK) == 0)
		unlink(".heredoc");
	if (data.pipe)
	{
		close(data.pipe[1]);
		free(data.pipe);
	}
	return (0);
}

pid_t	exec_cmd(t_vars *vars, t_exec_data data)
{
	pid_t	pid;
	char	**env;

	pid = fork();
	if (pid == -1)
		perror("Error on fork ");
	else if (pid == 0)
	{
		if (dup2(data.fd_in, 0) != 0)
			close(data.fd_in);
		if (dup2(data.fd_out, 1) != 1)
			close(data.fd_out);
		if (data.pipe)
		{
			close(data.pipe[0]);
			close(data.pipe[1]);
		}
		env = build_env(vars);
		execve(data.path, data.args, env);
		free_split(env);
		exit(1);
	}
	else if (data.pipe)
		close(data.pipe[1]);
	return (pid);
}

int	handle_pipe(t_vars *vars, t_exec_data *data, int *fd_in)
{
	int	*pipe_fd;

	if (vars->current_token->token.type == TOKEN_PIPE)
	{
		vars->current_token = vars->current_token->next;
		pipe_fd = calloc(2, sizeof(int));
		if (pipe(pipe_fd) == 0)
		{
			*fd_in = pipe_fd[0];
			data->pipe = pipe_fd;
			if (isatty(data->fd_out))
				data->fd_out = pipe_fd[1];
			return (1);
		}
	}
	*fd_in = 0;
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
	int			prev_fd;
	pid_t		pid;
	t_exec_data	data;


	vars->current_token = vars->token_list;
	use_pipe = 0;
	stop_signal(vars);
	while (vars->current_token->token.type != TOKEN_END)
	{
		data = build_exec(vars);
		if (use_pipe && isatty(data.fd_in))
			data.fd_in = prev_fd;
		else if (use_pipe)
			close(prev_fd);
		use_pipe = handle_pipe(vars, &data, &prev_fd);
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

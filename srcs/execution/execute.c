/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:56:53 by asene             #+#    #+#             */
/*   Updated: 2025/02/18 14:38:30 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// return exit code from waitpid status
static int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

// execve || exit
static void	exec_cmd(t_vars *vars, t_exec *data)
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

int	execute(t_vars *vars)
{
	int			exit_code;

	vars->exec_data = NULL;
	vars->nbheredoc = 0;
	stop_signal(vars);
	if (!build_exec(vars, vars->token_list, &vars->exec_data, NULL))
	{
		if (g_nal == SIGINT)
		{
			exit_code = 128 + SIGINT;
			g_nal = 0;
		}
		else
			exit_code = FAILURE;
	}
	else if (!vars->exec_data->args[0])
		exit_code = vars->exit_code;
	else if (vars->exec_data->pipe)
		exit_code = get_exit_code(execute_pipeline(vars, vars->exec_data, 0));
	else
		exit_code = run_cmd(vars, vars->exec_data, true);
	free_exec(vars->exec_data);
	start_signal(vars);
	heredoc_killer(vars->nbheredoc);
	return (exit_code);
}

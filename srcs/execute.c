/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:56:53 by asene             #+#    #+#             */
/*   Updated: 2025/01/08 23:53:24 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	end_exec(t_exec_data data, int pid, t_vars *vars)
{
	int		status;
	pid_t	wpid;

	if (data.path)
		free(data.path);
	if (data.args)
		free_split(data.args);
	wpid = waitpid(pid, &status, 0);
	start_signal(vars);
	if (wpid == -1)
		return (wpid);
	if (!WIFEXITED(status))
		return (-2);
	return (WEXITSTATUS(status));
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
		signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
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

void	execute(t_vars *vars)
{
	t_word_type	type;
	pid_t		pid;
	t_exec_data	data;

	vars->current_token = vars->token_list;
	while (vars->current_token->token.type != TOKEN_END)
	{
		data = build_exec(vars);
		type = cmd_or_file(vars, data.args[0]);
		if (type == W_BUILTIN)
			exec_builtin(vars, data);
		else if (type == W_CMD || type == W_EXECUTABLE)
		{
			stop_signal(vars);
			pid = exec_cmd(vars, data);
			end_exec(data, pid, vars);
		}
		else if (data.args[0])
			ft_fprintf(2, "%s: command not found\n", data.args[0]);
		if (vars->current_token->token.type == TOKEN_PIPE)
			vars->current_token = vars->current_token->next;
	}
	// else if (vars->current_token->token.type >= TOKEN_PIPE
	// 	&& vars->current_token->token.type <= TOKEN_HEREDOC)
	// 		syntax_check(vars);
}

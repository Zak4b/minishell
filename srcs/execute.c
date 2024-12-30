/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:56:53 by asene             #+#    #+#             */
/*   Updated: 2024/12/30 17:27:06 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	end_exec(t_exec_data data, int pid)
{
	int		status;
	pid_t	wpid;

	if (data.path)
		free(data.path);
	if (data.args)
		free_split(data.args);
	wpid = waitpid(pid, &status, 0);
	g_nal = 0;
	if (wpid == -1)
		return (wpid);
	if (!WIFEXITED(status))
		return (-2);
	return (WEXITSTATUS(status));
}

t_exec_data	build_exec(t_vars *vars)
{
	t_exec_data	data;
	t_list		*lst;
	t_tokenlist	*t;

	t = vars->current_token;
	lst = NULL;
	data.fd_in = 0;
	data.fd_out = 1;
	data.path = search_path(vars->env, t->token.value);
	while (t && (t->token.type == TOKEN_SPACE || t->token.type == TOKEN_WORD))
	{
		if (t->token.type == TOKEN_WORD)
			ft_lstadd_back(&lst, ft_lstnew(ft_strtrim(t->token.value, " ")));
		t = t->next;
	}
	vars->current_token = t;
	data.args = (char **)list_to_array(lst);
	ft_lstclear(&lst, NULL);
	return (data);
}

pid_t	exec_cmd(t_vars *vars, t_exec_data data)
{
	pid_t		pid;

	(void)vars;
	if (ft_strcmp("./minishell", data.path) == 0)
		g_nal = 2;
	pid = fork();
	if (pid == -1)
		perror("Error on fork ");
	else if (pid == 0)
	{
		if (dup2(data.fd_in, 0) != 0)
			close(data.fd_in);
		if (dup2(data.fd_out, 1) != 1)
			close(data.fd_out);
		execve(data.path, data.args, vars->env);
	}
	return (pid);
}

void	execute(t_vars *vars)
{
	t_word_type	type;
	pid_t		pid;
	t_exec_data	data;

	vars->current_token = vars->token_list;
	if (vars->current_token->token.type == TOKEN_WORD)
	{
		type = cmd_or_file(vars->current_token->token.value, vars->env);
		if (type == W_BUILTIN)
			exec_builtin(vars);
		else if (type == W_CMD || type == W_EXECUTABLE)
		{
			data = build_exec(vars);
			g_nal = 1;
			pid = exec_cmd(vars, data);
			end_exec(data, pid);
		}
		else if (vars->current_token->token.value)
			ft_fprintf(2, "%s: command not found\n",
				vars->current_token->token.value);
	}
}

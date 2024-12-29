/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:56:53 by asene             #+#    #+#             */
/*   Updated: 2024/12/29 14:14:01 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	end_exec(t_exec_data data, int pid)
{
	waitpid(pid, NULL, 0);
	if (data.path)
		free(data.path);
	if (data.args)
		free_split(data.args);
	g_nal = 0;
}

char	**list_to_array(t_list *lst)
{
	int		i;
	int		size;
	char	**array;

	size = ft_lstsize(lst);
	array = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (lst)
	{
		array[i++] = lst->content;
		lst = lst->next;
	}
	return (array);
}

t_exec_data	build_exec(t_vars *vars)
{
	t_exec_data	data;
	t_list		*string_lst;
	t_tokenlist	*t;

	t = vars->current_token;
	string_lst = NULL;
	data.path = search_path(vars->env, t->token.value);
	if (strcmp("./minishell", data.path) == 0)
		g_nal = 2;
	while (t && (t->token.type == TOKEN_SPACE || t->token.type == TOKEN_WORD))
	{
		if (t->token.type == TOKEN_WORD)
			ft_lstadd_back(&string_lst,
				ft_lstnew(ft_strtrim(t->token.value, " ")));
		t = t->next;
	}
	vars->current_token = t;
	data.args = list_to_array(string_lst);
	ft_lstclear(&string_lst, NULL);
	return (data);
}

pid_t	exec_cmd(t_vars *vars, t_exec_data data, int fd_in, int fd_out)
{
	pid_t		pid;

	(void)vars;
	pid = fork();
	if (pid == -1)
		perror("Error on fork ");
	else if (pid == 0)
	{
		if (0)
		{
			if (dup2(fd_in, 0) == -1 || dup2(fd_out, 1) == -1)
				return (perror("Error dup2 "), -1);
			close(fd_in);
			close(fd_out);
		}
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
			g_nal = 1;
			data = build_exec(vars);
			pid = exec_cmd(vars, data, 0, 1);
			if (pid > 0)
				end_exec(data, pid);
		}
		else if (vars->current_token->token.value)
			ft_printf("%s: command not found\n",
				vars->current_token->token.value);
	}
}

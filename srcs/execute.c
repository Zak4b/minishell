/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:56:53 by asene             #+#    #+#             */
/*   Updated: 2024/12/27 15:53:41 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*list_to_string(t_list *lst)
{
	int		i;
	int		size;
	char	**split;
	char	*res;

	size = ft_lstsize(lst);
	if (size == 0)
		return (NULL);
	split = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (lst)
	{
		split[i++] = lst->content;
		lst = lst->next;
	}
	res = ft_strnjoin(split, size, " ");
	free(split);
	return (res);
}

char	*build_word(t_tokenlist **lst)
{
	char 		*res;
	t_list		*string_lst;
	t_tokenlist	*t;

	t = *lst;
	string_lst = NULL;
	while (t && (t->token.type == TOKEN_SPACE || t->token.type == TOKEN_WORD))
	{
		ft_lstadd_back(&string_lst, ft_lstnew(ft_strdup(t->token.value)));
		t = t->next;
	}
	*lst = t;
	res = list_to_string(string_lst);
	ft_lstclear(&string_lst, free);
	if (res)
		res = ft_strtrim(res, " "); // Memory leak
	return (res);
}

pid_t	exec_cmd(t_vars *vars, t_exec_data data, int fd_in, int fd_out)
{
	static char	*args[] = {NULL, NULL, NULL};
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
		args[0] = data.cmd;
		args[1] = data.args;
		execve(args[0], args, vars->env);
	}
	return (pid);
}

void	execute(t_vars *vars)
{
	t_word_type	type;
	t_exec_data	data;
	pid_t		pid;

	vars->current_token = vars->token_list;
	if (vars->current_token->token.type == TOKEN_WORD)
	{
		data.cmd = vars->current_token->token.value;
		type = cmd_or_file(data.cmd, vars->env);
		if (type == W_BUILTIN)
			exec_builtin(vars);
		else if (type == W_CMD || type == W_EXECUTABLE)
		{
			data.cmd = search_path(vars->env, data.cmd);
			data.args = build_word(&vars->current_token->next);
			pid = exec_cmd(vars, data, 0, 1);
			if (pid > 0)
				waitpid(pid, NULL, 0);
		}
	}
}

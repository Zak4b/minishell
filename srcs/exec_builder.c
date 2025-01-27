/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:45:46 by asene             #+#    #+#             */
/*   Updated: 2025/01/27 13:46:21 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_exec(t_exec *data)
{
	if (data->path)
		free(data->path);
	if (data->args)
		free_split(data->args);
	if (data->fd_out != 1 && data->fd_out != -1)
		close(data->fd_out);
	if (data->fd_in != 0 && data->fd_in != -1)
		close(data->fd_in);
	if (data->pipe)
		free_exec(data->pipe);
	free(data);
}

char	*build_word(t_vars *vars, t_token **lst, bool *has_quote)
{
	char	*value;
	char	*tmp;
	bool	quote;

	if (has_quote)
		*has_quote = false;
	value = ft_calloc(1, sizeof(char));
	while (*lst)
	{
		tmp = eval_string(vars, (*lst)->value, &quote);
		if (has_quote && quote)
			*has_quote = true;
		str_append(&value, tmp);
		free(tmp);
		if (((*lst)->next && (*lst)->next->type != TOKEN_WORD)
			|| (*lst)->next == NULL )
			break ;
		(*lst) = (*lst)->next;
	}
	return (value);
}

int	open_redirection(t_vars *vars, t_token_type type, t_token **tok_lst)
{
	int		fd;
	int		flags;
	char	*name;
	bool	has_quote;

	name = build_word(vars, tok_lst, &has_quote);
	if (type == TOKEN_HEREDOC)
		fd = heredoc(vars, name, !has_quote);
	else
	{
		flags = 0;
		if (type == TOKEN_REDIRECT_OUT)
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		else if (type == TOKEN_APPEND)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else if (type == TOKEN_REDIRECT_IN)
			flags = O_RDONLY;
		fd = open(name, flags, 0644);
	}
	if (fd == -1 && type != TOKEN_HEREDOC)
		file_error(name);
	free(name);
	return (fd);
}

bool	handle_redirect(t_vars *vars, t_exec *data, t_token **tok_lst)
{
	int		fd;
	t_token	current;

	current = **tok_lst;
	(*tok_lst) = (*tok_lst)->next;
	fd = open_redirection(vars, current.type, tok_lst);
	if (current.type == TOKEN_REDIRECT_OUT || current.type == TOKEN_APPEND)
	{
		if (data->fd_out != 1)
			close(data->fd_out);
		data->fd_out = fd;
	}
	if (current.type == TOKEN_REDIRECT_IN || current.type == TOKEN_HEREDOC)
	{
		if (data->fd_in != 0)
			close(data->fd_in);
		data->fd_in = fd;
	}
	return (fd != -1);
}

t_exec	*build_exec(t_vars *vars, t_token *tok_lst, t_exec **data, t_exec *prev)
{
	t_list	*lst;

	lst = NULL;
	vars->tmp = &lst;
	*data = ft_calloc(1, sizeof(t_exec));
	**data = (t_exec){NULL, NULL, 0, 0, 1, NULL, NULL};
	(*data)->prev = prev;
	while (tok_lst && ! is_limit_token(*tok_lst))
	{
		if (tok_lst->type == TOKEN_WORD)
			ft_lstadd_back(&lst, ft_lstnew(build_word(vars, &tok_lst, NULL)));
		else if (is_redirection(*tok_lst))
			handle_redirect(vars, *data, &tok_lst);
		tok_lst = tok_lst->next;
	}
	(*data)->args = (char **)ft_lst_to_array(lst);
	ft_lstclear(&lst, NULL);
	(*data)->path = search_path(vars, (*data)->args[0]);
	if (tok_lst && tok_lst->type == TOKEN_PIPE)
		build_exec(vars, tok_lst->next, &(*data)->pipe, *data);
	return ((*data)->argc = count_line((*data)->args), *data);
}

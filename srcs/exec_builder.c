/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:45:46 by asene             #+#    #+#             */
/*   Updated: 2025/01/21 13:07:56 by asene            ###   ########.fr       */
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

char	*replace_vars(t_vars *vars, char *str)
{
	int		i;
	t_list	*lst;
	char	*var;
	char	**array;

	lst = NULL;
	while (*str)
	{
		i = 0;
		while (str[i] && str[i] != '$')
			i++;
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, 0, i)));
		str = str + i;
		if (*str == '$' && ++str)
		{
			var = grab_word(&str);
			ft_lstadd_back(&lst, ft_lstnew(getenv_value(vars, var)));
			free(var);
		}
	}
	array = (char **)list_to_array(lst);
	var = ft_strnjoin(array, count_line(array), "");
	return (ft_lstclear(&lst, NULL), free_split(array), var);
}

char	*eval_string(t_vars *vars, char *str)
{
	char	*p;
	char	*res;
	char	quote;

	p = NULL;
	quote = 0;
	if (ft_strchr("'\"", *str))
	{
		quote = *str;
		if (str[ft_strlen(str) - 1] != str[0])
			return (NULL);
		p = ft_strdup(str + 1);
		str = p;
		str[ft_strlen(str) - 1] = '\0';
	}
	if (quote == '\'')
		res = ft_strdup(str);
	else
		res = replace_vars(vars, str);
	if (p)
		free (p);
	return (res);
}

char	*build_word(t_vars *vars, t_tokenlist **lst)
{
	char	*value;
	char	*tmp;

	value = ft_calloc(1, sizeof(char));
	while ((*lst)->token.type == TOKEN_WORD)
	{
		tmp = eval_string(vars, (*lst)->token.value);
		str_append(&value, tmp);
		free(tmp);
		(*lst) = (*lst)->next;
	}
	return (value);
}

void	file_error(t_token token)
{
	if (access(token.value, F_OK) == 0)
		ft_fprintf(2, "minishell: %s: Permission denied\n", token.value);
	else
		ft_fprintf(2, "minishell: %s: No such file or directory\n", token.value);
}

void	handle_redirect(t_vars *vars, t_exec_data *data, t_token token)
{
	int	fd;

	if (token.type == TOKEN_REDIRECT_OUT)
		fd = open(token.value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (token.type == TOKEN_APPEND)
		fd = open(token.value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (token.type == TOKEN_REDIRECT_IN)
		fd = open(token.value, O_RDONLY);
	else
		fd = heredoc(token.value, vars);
	if (fd == -1)
		file_error(token);
	if (token.type == TOKEN_REDIRECT_OUT || token.type == TOKEN_APPEND)
	{
		if (data->fd_out != 1)
			close(data->fd_out);
		data->fd_out = fd;
	}
	if (token.type == TOKEN_REDIRECT_IN || token.type == TOKEN_HEREDOC)
	{
		if (data->fd_in != 0)
			close(data->fd_in);
		data->fd_in = fd;
	}
}

t_exec_data	*build_exec(t_vars *vars, t_tokenlist *tok_lst, t_exec_data **data)
{
	t_list		*lst;

	lst = NULL;
	if (!*data)
		*data = ft_calloc(1, sizeof(t_exec_data));
	**data = (t_exec_data){NULL, NULL, 0, 0, 1, NULL};
	while (tok_lst && tok_lst->token.type != TOKEN_PIPE
		&& tok_lst->token.type != TOKEN_END)
	{
		if (tok_lst->token.type == TOKEN_WORD)
		{
			ft_lstadd_back(&lst, ft_lstnew(build_word(vars, &tok_lst)));
			continue ;
		}
		else if (tok_lst->token.type >= TOKEN_REDIRECT_IN
			&& tok_lst->token.type <= TOKEN_HEREDOC)
			handle_redirect(vars, *data, tok_lst->token);
		tok_lst = tok_lst->next;
	}
	(*data)->args = (char **)list_to_array(lst);
	if ((*data)->args[0])
		(*data)->path = search_path(vars, (*data)->args[0]);
	if (tok_lst->token.type == TOKEN_PIPE)
		build_exec(vars, tok_lst->next, &(*data)->pipe);
	return (ft_lstclear(&lst, NULL), (*data)->argc = count_line((*data)->args), *data);
}

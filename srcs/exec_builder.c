/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:45:46 by asene             #+#    #+#             */
/*   Updated: 2025/01/10 13:50:23 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*replace_vars(t_vars *vars, char *str)
{
	int		i;
	t_list	*lst;
	char	*var;
	char	**array;
	char	*res;

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
			str += ft_strlen(var);
			free(var);
		}
	}
	array = (char **)list_to_array(lst);
	res = ft_strnjoin(array, count_line(array), "");
	return (ft_lstclear(&lst, NULL), free_split(array), res);
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

void	handle_redirect(t_vars *vars, t_exec_data *data, t_token token)
{
	int	fd;

	vars->current_token = vars->current_token->next;
	if (token.type == TOKEN_REDIRECT_OUT)
		fd = open(token.value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (token.type == TOKEN_APPEND)
		fd = open(token.value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (token.type == TOKEN_REDIRECT_IN)
		fd = open(token.value, O_RDONLY);
	else
		fd = open(heredoc(token.value, vars), O_RDONLY);
	if (fd == -1)
		return ;
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

t_exec_data	build_exec(t_vars *vars)
{
	t_exec_data	data;
	t_list		*lst;
	t_tokenlist	**t;

	t = &vars->current_token;
	lst = NULL;
	data = (t_exec_data){NULL, NULL, 0, 0, 1, NULL};
	while ((*t) && (*t)->token.type != TOKEN_PIPE
		&& (*t)->token.type != TOKEN_END)
	{
		if ((*t)->token.type == TOKEN_WORD)
			ft_lstadd_back(&lst, ft_lstnew(build_word(vars, t)));
		else if ((*t)->token.type >= TOKEN_REDIRECT_IN
			&& (*t)->token.type <= TOKEN_HEREDOC)
			handle_redirect(vars, &data, (*t)->token);
		else
			(*t) = (*t)->next;
	}
	data.args = (char **)list_to_array(lst);
	if (data.args[0])
		data.path = search_path(vars, data.args[0]);
	return (ft_lstclear(&lst, NULL), data.argc = count_line(data.args), data);
}

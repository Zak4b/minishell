/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:32:57 by asene             #+#    #+#             */
/*   Updated: 2025/01/22 22:28:31 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*grab_var_name(char **p)
{
	int		i;
	char	*res;

	if (**p == '?')
		return ((*p)++, ft_strdup("?"));
	i = 0;
	while ((*p)[i])
	{
		if (ft_isspace((*p)[i]) || ft_strchr("$|<>/\"'", (*p)[i]))
			break ;
		i++;
	}
	return (res = ft_substr(*p, 0, i), *p += i, res);
}

char	*get_var_value(t_vars *vars, char **p)
{
	char	*var_name;
	char	*value;

	var_name = grab_var_name(p);
	if (ft_strlen(var_name) == 0)
		value = ft_strdup("$");
	else
		value = getenv_value(vars, var_name);
	free(var_name);
	if (value)
		return (value);
	else
		return (ft_strdup(""));
}

char	*replace_vars(t_vars *vars, char *str)
{
	int		i;
	t_list	*lst;
	char	*result;
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
			ft_lstadd_back(&lst, ft_lstnew(get_var_value(vars, &str)));
	}
	array = (char **)ft_lst_to_array(lst);
	result = ft_strnjoin(array, count_line(array), "");
	return (ft_lstclear(&lst, NULL), free_split(array), result);
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

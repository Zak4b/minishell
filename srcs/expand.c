/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:32:57 by asene             #+#    #+#             */
/*   Updated: 2025/02/18 14:44:50 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*grab_var_name(char **p)
{
	int		i;
	char	*res;

	if (**p == '?')
		return ((*p)++, ft_strdup("?"));
	i = 0;
	while ((*p)[i] && (isalnum((*p)[i]) || (*p)[i] == '_'))
		i++;
	return (res = ft_substr(*p, 0, i), *p += i, res);
}

char	*replace_vars(t_vars *vars, char *str)
{
	int		i;
	t_list	*lst;
	char	*var_name;
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
		{
			var_name = grab_var_name(&str);
			ft_lstadd_back(&lst, ft_lstnew(get_var_string(vars, var_name)));
			free(var_name);
		}
	}
	array = (char **)ft_lst_to_array(lst);
	result = ft_strnjoin(array, count_line(array), "");
	return (ft_lstclear(&lst, NULL), free_split(array), result);
}

char	*eval_string(t_vars *vars, char *str, bool *has_quote)
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
	if (has_quote)
		*has_quote = (quote != 0);
	if (p)
		free (p);
	return (res);
}

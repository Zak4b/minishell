/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:30:27 by asene             #+#    #+#             */
/*   Updated: 2025/02/18 14:30:35 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec(t_exec *data)
{
	if (!data)
		return ;
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
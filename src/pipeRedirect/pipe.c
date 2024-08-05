/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:27:58 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/22 20:07:55 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe_fd	*create_pipe(t_ats *ats)
{
	int			i;
	t_ats		*tmp_ats;
	t_pipe_fd	*fd;

	i = 0;
	tmp_ats = ats;
	fd = (t_pipe_fd *)malloc(sizeof(t_pipe_fd));
	if (!fd)
		ft_error("minishell", NULL, "malloc failed", 1);
	fd->fd = (int *)malloc(sizeof(int) * (ats_list_size(ats) - 1) * 2);
	if (!fd->fd)
		ft_error("minishell", NULL, "malloc failed", 1);
	while (tmp_ats && tmp_ats->next)
	{
		if (pipe(fd->fd + 2 * i) == -1)
			ft_error("minishell", NULL, "pipe failed", 1);
		tmp_ats = tmp_ats->next;
		i++;
	}
	fd->pipe_size = i;
	return (fd);
}

void	close_pipe(t_pipe_fd *fdp)
{
	int		i;

	i = 0;
	if (!fdp || fdp->pipe_size == 0)
		return ;
	fdp->pipe_size *= 2;
	while (i < fdp->pipe_size)
	{
		if (fdp->fd[i] != 0 && fdp->fd[i] != 1)
			close(fdp->fd[i]);
		i++;
	}
}

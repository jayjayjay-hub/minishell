/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:27:21 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/24 13:11:00 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dp_free(char **arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		free(arg[i]);
	free(arg);
}

void	free_command(t_cmd *command)
{
	if (!command)
		return ;
	if (command->fdp)
	{
		if (command->fdp->fd)
			free(command->fdp->fd);
		free(command->fdp);
	}
	if (command->pid_info.pid)
		free(command->pid_info.pid);
	if (command->ats)
		free_ats(command->ats);
	free(command);
}

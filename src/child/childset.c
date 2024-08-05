/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:50:27 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/22 20:07:55 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_loop(t_cmd *command, t_env *env)
{
	while (command->ats)
	{
		command->pid_info.pid[command->pid_info.pipe_i] = child(command, env);
		command->pid_info.pipe_i++;
		command->ats = command->ats->next;
	}
}

void	wait_child(t_pid_info pid_info)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (pid_info.pipe_i--)
	{
		waitpid(pid_info.pid[i++], &status, 0);
		if (status == 2)
			status = 130 * 256;
		error_status(WEXITSTATUS(status));
		register_signal();
	}
}

void	make_wait_child(t_cmd *command, t_env *env)
{
	t_ats	*tmp;

	tmp = command->ats;
	command->fdp = create_pipe(command->ats);
	command->pid_info.pid = (pid_t *)malloc(sizeof(pid_t)
			* (command->fdp->pipe_size + 1));
	if (!command->fdp->pipe_size
		&& builtin_control(command->ats->token,
			&env, 0, command->fdp->pipe_size))
	{
		close_redirect(command->ats->token);
		error_status(PRINT_ERROR);
		return ;
	}
	execve_loop(command, env);
	close_pipe(command->fdp);
	wait_child(command->pid_info);
	if (!command->fdp->pipe_size && builtin_check(tmp->token, 0))
		close_redirect(tmp->token);
	free_ats(tmp);
}

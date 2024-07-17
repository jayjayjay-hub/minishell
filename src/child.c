/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:26:38 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/17 15:26:41 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sub_dup2(int first, int second)
{
	if (first != 0)
		dup2(first, STDIN_FILENO);
	if (second != 0)
		dup2(second, STDOUT_FILENO);
}

char	*search_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*tmp_ret;
	char	*ret;

	i = 0;
	while (*envp && ft_strncmp(*envp, "PATH", 4))
		envp++;
	paths = ft_split(*envp + 5, ':');
	while (paths[i])
	{
		tmp_ret = ft_strjoin(paths[i], "/");
		ret = ft_strjoin(tmp_ret, cmd);
		if (access(ret, F_OK) == 0)
		{
			dp_free(paths);
			free(tmp_ret);
			return (ret);
		}
		free(tmp_ret);
		free(ret);
		i++;
	}
	dp_free(paths);
	return (NULL);
}

void	do_execve(char **cmd, char **envp)
{
	char	*path;

	path = NULL;
	if (!ft_strncmp(cmd[0], "/", 1) || !ft_strncmp(cmd[0], "./", 2))
	{
		if (access(cmd[0], F_OK) != -1)
			path = cmd[0];
		else
			ft_error("minishell", cmd[0],
				"No such file or directory", CMD_NOT_FOUND);
	}
	else
		path = search_path(cmd[0], envp);
	if (!path)
		ft_error("minishell", cmd[0], "command not found", CMD_NOT_FOUND);
	if (execve(path, cmd, envp) == -1)
		ft_error(NULL, NULL, "execve failed", EXIT_FAILURE);
}

void	**run_cmd(t_ats *ats, char **envp)
{
	int			i;
	char		**cmd;
	t_token		*token;

	i = 0;
	token = ats->token;
	cmd = (char **)ft_calloc(token_list_size(token) + 1, sizeof(char *));
	if (!cmd)
		ft_error("malloc", "cmd", "malloc failed", 1);
	while (token)
	{
		while (token && token->type == WORD)
		{
			cmd[i] = ft_strdup(token->str);
			if (!cmd[i])
				ft_error("malloc", "cmd", "malloc failed", 1);
			token = token->next;
			i++;
		}
		if (!redirect(&token))
			exit(error_status(256 * 1));
	}
	free_ats(ats);
	do_execve(cmd, envp);
	return (NULL);
}

pid_t	child(t_cmd *command, t_env *env)
{
	pid_t	pid;
	int		pipe_i;

	pid = fork();
	if (pid == -1)
		ft_error("minishell", NULL, "fork failed", 1);
	if (pid == 0)
	{
		pipe_i = command->pid_info.pipe_i;
		if (command->fd_pipe->pipe_size != 0)
		{
			if (pipe_i == 0)
				sub_dup2(0, command->fd_pipe->fd[2 * pipe_i + 1]);
			else if (pipe_i == command->fd_pipe->pipe_size)
				sub_dup2(command->fd_pipe->fd[2 * pipe_i - 2], 0);
			else
				sub_dup2(command->fd_pipe->fd[2 * pipe_i - 2],
					command->fd_pipe->fd[2 * pipe_i + 1]);
		}
		close_pipe(command->fd_pipe);
		if (builtin_control(command->ats->token, &env, 1))
			exit(error_status(PRINT_ERROR));
		run_cmd(command->ats, command->envp);
	}
	return (pid);
}

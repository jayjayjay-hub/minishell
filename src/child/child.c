/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:26:38 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/24 12:13:41 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sub_dup2(int first, int second)
{
	if (first != 0)
	{
		if (dup2(first, STDIN_FILENO) == -1)
			ft_error("minishell", NULL, "dup2 failed", 1);
	}
	if (second != 0)
	{
		if (dup2(second, STDOUT_FILENO) == -1)
			ft_error("minishell", NULL, "dup2 failed", 1);
	}
}

char	*search_path(char *cmd, t_env *env)
{
	int		i;
	char	*ret;
	char	*tmp;
	char	**paths;
	char	*tmp_ret;

	i = 0;
	tmp = get_env_value("PATH", env);
	if (!tmp)
		ft_error("minishell", cmd, "No such file or directory", CMD_NOT_FOUND);
	paths = ft_split(tmp, ':');
	free(tmp);
	while (paths[i])
	{
		tmp_ret = ft_strjoin(paths[i], "/");
		ret = ft_strjoin(tmp_ret, cmd);
		if (access(ret, F_OK) == 0)
			return (dp_free(paths), free(tmp_ret), ret);
		free(tmp_ret);
		free(ret);
		i++;
	}
	dp_free(paths);
	return (NULL);
}

void	do_execve(char **cmd, char **envp, t_env *env)
{
	char	*path;

	path = NULL;
	if (!cmd[0])
		exit(0);
	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], F_OK) != -1)
			path = cmd[0];
		else
			ft_error("minishell", cmd[0],
				"No such file or directory", CMD_NOT_FOUND);
	}
	else
		path = search_path(cmd[0], env);
	if (!path)
		ft_error("minishell", cmd[0], "command not found", CMD_NOT_FOUND);
	if (cmd[0][0] == '\0')
		ft_error("minishell", "\'\'", "command not found", CMD_NOT_FOUND);
	if (execve(path, cmd, envp) == -1)
		ft_error(NULL, NULL, "execve failed", EXIT_FAILURE);
}

void	**run_cmd(t_ats *ats, char **envp, t_env *env)
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
			exit(error_status(1));
	}
	free_ats(ats);
	do_execve(cmd, envp, env);
	return (NULL);
}

pid_t	child(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		pi;

	sig_quit_set();
	pid = fork();
	if (pid == -1)
		ft_error("minishell", NULL, "fork failed", 1);
	if (pid == 0)
	{
		pi = cmd->pid_info.pipe_i;
		if (cmd->fdp->pipe_size != 0)
		{
			if (pi == 0)
				sub_dup2(0, cmd->fdp->fd[2 * pi + 1]);
			else if (pi == cmd->fdp->pipe_size)
				sub_dup2(cmd->fdp->fd[2 * pi - 2], 0);
			else
				sub_dup2(cmd->fdp->fd[2 * pi - 2], cmd->fdp->fd[2 * pi + 1]);
		}
		close_pipe(cmd->fdp);
		if (builtin_control(cmd->ats->token, &env, 1, 1))
			exit(error_status(PRINT_ERROR));
		run_cmd(cmd->ats, cmd->envp, env);
	}
	return (sig_child(), pid);
}

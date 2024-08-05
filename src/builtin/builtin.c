/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:26:24 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/24 15:22:38 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	builtin_check(t_token *token, int echo_check)
{
	if (ft_strlen(token->str) == 4 && !ft_strncmp(token->str, "exit", 4))
		return (true);
	if (ft_strlen(token->str) == 2 && !ft_strncmp(token->str, "cd", 3))
		return (true);
	if (ft_strlen(token->str) == 4 && !ft_strncmp(token->str, "echo", 5)
		&& echo_check)
		return (true);
	if (ft_strlen(token->str) == 3 && !ft_strncmp(token->str, "pwd", 4))
		return (true);
	if (ft_strlen(token->str) == 6 && !ft_strncmp(token->str, "export", 7))
		return (true);
	if (ft_strlen(token->str) == 3 && !ft_strncmp(token->str, "env", 4))
		return (true);
	if (ft_strlen(token->str) == 5 && !ft_strncmp(token->str, "unset", 6))
		return (true);
	return (false);
}

bool	do_builtin(t_token *token, t_env **env, int child_check)
{
	while (token)
	{
		if (ft_strlen(token->str) == 4 && !ft_strncmp(token->str, "exit", 4))
		{
			if (child_check)
				return (builtin_exit_child(token));
			return (builtin_exit(token));
		}
		if (ft_strlen(token->str) == 2 && !ft_strncmp(token->str, "cd", 3))
			return (builtin_cd(token, env));
		if (ft_strlen(token->str) == 4 && !ft_strncmp(token->str, "echo", 5))
			return (builtin_echo(token));
		if (ft_strlen(token->str) == 3 && !ft_strncmp(token->str, "pwd", 4))
			return (builtin_pwd());
		if (ft_strlen(token->str) == 6 && !ft_strncmp(token->str, "export", 7))
			return (builtin_export(token, env));
		if (ft_strlen(token->str) == 3 && !ft_strncmp(token->str, "env", 4))
			return (builtin_env(token, *env));
		if (ft_strlen(token->str) == 5 && !ft_strncmp(token->str, "unset", 6))
			return (builtin_unset(token, env));
		token = token->next;
	}
	return (true);
}

bool	builtin_control(t_token *token,
						t_env **env, int child_check, int echo_check)
{
	t_token	*tmp;

	if (!builtin_check(token, echo_check))
		return (false);
	tmp = token;
	while (tmp)
	{
		while (tmp && tmp->type == WORD)
			tmp = tmp->next;
		if (!redirect(&tmp))
			return (true);
	}
	return (do_builtin(token, env, child_check));
}

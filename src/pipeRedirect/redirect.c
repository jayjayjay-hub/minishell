/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:28:02 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/22 17:02:01 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	redirect(t_token **token)
{
	if (!*token)
		return (true);
	if ((*token)->fd < 0)
		return (false);
	if ((*token)->type == REDIRECT_IN || (*token)->type == REDIRECT_HERE_DOC)
	{
		(*token)->backup_fd = dup(STDIN_FILENO);
		if ((*token)->backup_fd == -1)
			ft_error("minishell", NULL, "dup failed", 1);
		if (dup2((*token)->fd, STDIN_FILENO) == -1)
			ft_error("minishell", NULL, "dup2 failed", 1);
	}
	else
	{
		(*token)->backup_fd = dup(STDOUT_FILENO);
		if ((*token)->backup_fd == -1)
			ft_error("minishell", NULL, "dup failed", 1);
		if (dup2((*token)->fd, STDOUT_FILENO) == -1)
			ft_error("minishell", NULL, "dup2 failed", 1);
	}
	if (close((*token)->fd) == -1)
		ft_error("minishell", NULL, "cfase failed", 1);
	*token = (*token)->next;
	*token = (*token)->next;
	return (true);
}

bool	redirect_open(t_token *token, t_env *env)
{
	while (token)
	{
		if (token->type == REDIRECT_IN)
			token->fd = open(token->next->str, O_RDONLY);
		else if (token->type == REDIRECT_OUT)
			token->fd = open(token->next->str,
					O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
		else if (token->type == REDIRECT_APPEND)
			token->fd = open(token->next->str,
					O_WRONLY | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
		else if (token->type == REDIRECT_HERE_DOC)
			token->fd = open_heredoc(token->next->str, env);
		if (token->fd == 130)
			return (false);
		if (token->fd == -1)
			ft_error("minishell", token->next->str,
				"No such file or directory", 0);
		token = token->next;
	}
	return (true);
}

void	close_redirect(t_token *token)
{
	while (token->next)
		token = token->next;
	while (token->prev)
	{
		if (token->type == REDIRECT_IN || token->type == REDIRECT_HERE_DOC)
		{
			if (dup2(token->backup_fd, STDIN_FILENO) == -1)
				ft_error("minishell", "error", "dup2 failed", 1);
			if (close(token->backup_fd) == -1)
				ft_error("minishell", "close", "close failed", 1);
		}
		else if (token->type == REDIRECT_OUT || token->type == REDIRECT_APPEND)
		{
			if (dup2(token->backup_fd, STDOUT_FILENO) == -1)
				ft_error("minishell", "error", "dup2 failed", 1);
			if (close(token->backup_fd) == -1)
				ft_error("minishell", "close", "close failed", 1);
		}
		token = token->prev;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:28:14 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/22 18:39:09 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_syntax_error(t_token *token)
{
	if (!token->next)
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			2);
	else if (token->next->type != WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token->str, 2);
		ft_putendl_fd("'", 2);
	}
}

bool	syntax_check(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return (false);
	tmp = token;
	while (tmp)
	{
		if (tmp->type >= PIPE && tmp->type <= REDIRECT_APPEND)
		{
			if (!tmp->next || tmp->next->type != WORD)
			{
				put_syntax_error(tmp);
				error_status(2);
				free_token(token);
				return (false);
			}
		}
		tmp = tmp->next;
	}
	return (true);
}

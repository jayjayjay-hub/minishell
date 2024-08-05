/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:25:46 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/17 15:25:48 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_option(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (false);
	else
	{
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i])
			return (false);
	}
	return (true);
}

bool	builtin_echo(t_token *token)
{
	bool	newline;

	newline = true;
	if (token->next && check_option(token->next->str))
	{
		newline = false;
		token = token->next;
	}
	token = token->next;
	while (token && check_option(token->str))
		token = token->next;
	while (token && token->type == WORD)
	{
		ft_putstr_fd(token->str, 1);
		token = token->next;
		if (token)
			ft_putstr_fd(" ", 1);
	}
	if (newline)
		ft_putendl_fd(NULL, 1);
	error_status(0);
	return (true);
}

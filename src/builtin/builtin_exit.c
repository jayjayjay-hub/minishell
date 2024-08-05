/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:26:00 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/22 19:13:43 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (false);
		i++;
	}
	return (true);
}

bool	builtin_exit(t_token *token)
{
	int	ret;

	ret = 0;
	ft_putendl_fd("exit", 1);
	if (!token->next)
		exit(error_status(PRINT_ERROR));
	else if (!ft_strncmp(token->next->str, "$", 1))
		exit(error_status(0));
	else if (!ft_str_isdigit(token->next->str))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(token->next->str, 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(error_status(2));
		return (true);
	}
	else if (token_list_size(token) > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		error_status(1);
		return (true);
	}
	else
		ret = (size_t)ft_atoi(token->next->str);
	exit(ret);
}

bool	builtin_exit_child(t_token *token)
{
	int	ret;

	ret = 0;
	if (!token->next)
		exit(error_status(0));
	else if (!ft_strncmp(token->next->str, "$", 1))
		exit(error_status(0));
	else if (!ft_str_isdigit(token->next->str))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(token->next->str, 2);
		ft_putendl_fd(": numeric argument required", 2);
		error_status(2);
		return (true);
	}
	else if (token_list_size(token) > 2)
	{
		error_status(1);
		return (true);
	}
	else
		ret = (size_t)ft_atoi(token->next->str);
	exit(ret);
}

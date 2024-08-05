/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:26:07 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/22 15:13:02 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && tmp->is_export)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->key, 1);
		if (tmp->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putendl_fd("\"", 1);
		}
		else
			ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
}

bool	builtin_export(t_token *token, t_env **env)
{
	t_env	*new;

	if (!token->next)
		return (print_export(*env), true);
	token = token->next;
	while (token)
	{
		new = new_env(token->str, true, env);
		env_add_back(new, env);
		token = token->next;
	}
	return (error_status(0), true);
}

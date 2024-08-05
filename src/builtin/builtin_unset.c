/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:25:04 by jtakahas          #+#    #+#             */
/*   Updated: 2024/07/22 15:49:28 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// builtin_unset.c

#include "minishell.h"

void	unset(char *key, t_env **env)
{
	t_env	*tmp;
	t_env	*prev;
	int		key_len;

	prev = NULL;
	tmp = *env;
	key_len = ft_strlen(key);
	while (tmp)
	{
		if ((int)ft_strlen(tmp->key) == key_len
			&& !ft_strncmp(tmp->key, key, key_len))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

bool	builtin_unset(t_token *token, t_env **env)
{
	if (!token->next)
		return (true);
	token = token->next;
	while (token)
	{
		unset(token->str, env);
		token = token->next;
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ats_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:30:07 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/17 15:30:08 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back_ats(t_ats **list, t_ats *new)
{
	t_ats	*tmp;

	if (!list || !new)
		return ;
	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

t_ats	*new_ats(t_token *token)
{
	t_ats	*ats;
	t_token	*tmp;

	ats = malloc(sizeof(t_ats));
	if (!ats)
		ft_error("malloc", "ats", strerror(errno), EXIT_FAILURE);
	tmp = NULL;
	while (token && token->type != PIPE)
	{
		token_add_back(&tmp, new_token(token->str, token->type, token->fd));
		token = token->next;
	}
	if (tmp)
	{
		ats->token = tmp;
		ats->next = NULL;
		ats->prev = NULL;
	}
	else
	{
		free_ats(ats);
		ats = NULL;
	}
	return (ats);
}

void	free_ats(t_ats *ats)
{
	t_ats	*tmp;

	while (ats)
	{
		tmp = ats->next;
		free_token(ats->token);
		if (!tmp)
		{
			free(ats);
			break ;
		}
		free(ats);
		ats = tmp;
	}
}

int	ats_list_size(t_ats *ats)
{
	int		size;

	size = 0;
	while (ats)
	{
		size++;
		ats = ats->next;
	}
	return (size);
}

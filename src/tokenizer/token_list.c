/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:29:38 by jtakahas          #+#    #+#             */
/*   Updated: 2024/07/24 14:29:39 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_add_back(t_token **list, t_token *new)
{
	t_token	*tmp;

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

t_token	*new_token(char *str, t_token_type type, int fd)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		ft_error("malloc", "token", strerror(errno), EXIT_FAILURE);
	if (type != WORD)
	{
		token->str = ft_strdup(str);
		if (!token->str)
			ft_error("ft_strdup", "token->str", strerror(errno), EXIT_FAILURE);
	}
	else
	{
		token->str = ft_strdup(str);
		if (!token->str)
			ft_error("ft_strdup", "token->str", strerror(errno), EXIT_FAILURE);
	}
	token->type = type;
	token->fd = fd;
	token->backup_fd = -1;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

bool	delete_token(t_token **token)
{
	t_token	*tmp;
	t_token	*nepre;
	bool	ret;

	ret = false;
	if (!token || !*token)
		return (false);
	tmp = *token;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (tmp->next)
	{
		nepre = tmp->next;
		ret = true;
	}
	else
		nepre = tmp->prev;
	free(tmp->str);
	free(tmp);
	*token = nepre;
	return (ret);
}

int	token_list_size(t_token *token)
{
	long long		size;

	size = 0;
	while (token)
	{
		if (size == INT_MAX)
			return (-1);
		size++;
		token = token->next;
	}
	return (size);
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->str)
			free(token->str);
		if (!tmp)
		{
			free(token);
			break ;
		}
		free(token);
		token = tmp;
	}
}

// void	print_token(t_token *token)
// {
// 	if (token == NULL)
// 	{
// 		printf("token is NULL\n");
// 		return ;
// 	}
// 	printf("token size: %d\n", token_list_size(token));
// 	while (token)
// 	{
// 		printf("str: '%s'\n", token->str);
// 		printf("type: %d\n", token->type);
// 		printf("fd: %d\n", token->fd);
// 		printf("backup_fd: %d\n", token->backup_fd);
// 		printf("next: %p\n", token->next);
// 		printf("prev: %p\n", token->prev);
// 		token = token->next;
// 	}
// }

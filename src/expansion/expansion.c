/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:50:58 by jtakahas          #+#    #+#             */
/*   Updated: 2024/07/24 15:54:21 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*variable_expansion(char *str, t_env *env, int *str_index)
{
	char	*key;
	char	*value;

	str++;
	key = get_key(str);
	if (!key)
	{
		*str_index += 2;
		return (NULL);
	}
	value = get_env_value(key, env);
	*str_index += ft_strlen(key) + 1;
	free(key);
	return (value);
}

char	*pass_single_quote(char *str, int *str_index)
{
	int	index;

	index = 0;
	index++;
	while (str[index] && !is_single_quote(str[index]))
		index++;
	index++;
	*str_index += index;
	return (ft_substr(str, 0, index));
}

void	pass_double_quote(char *str, char **tmp, int *index, t_env *env)
{
	join_and_free(tmp, ft_substr(str + *index, 0, 1));
	(*index)++;
	while (str[*index] && !is_double_quote(str[*index]))
	{
		if (str[*index] == '$' && str[(*index) + 1])
			join_and_free(tmp, variable_expansion(str + *index, env, index));
		else
		{
			join_and_free(tmp, ft_substr(str + *index, 0, 1));
			(*index)++;
		}
	}
	join_and_free(tmp, ft_substr(str + *index, 0, 1));
	(*index)++;
}

void	expansion_env(char **str, t_env *env)
{
	int		index;
	char	*tmp;

	index = 0;
	tmp = ft_calloc(1, sizeof(char) * (ft_strlen(*str) + 1));
	while ((*str)[index])
	{
		if (is_double_quote((*str)[index]))
			pass_double_quote(*str, &tmp, &index, env);
		else if (is_single_quote((*str)[index]))
			join_and_free(&tmp, pass_single_quote(*str + index, &index));
		else if ((*str)[index] == '$' && (*str)[index + 1])
			join_and_free(&tmp, variable_expansion(*str + index, env, &index));
		else if ((*str)[index])
		{
			join_and_free(&tmp, ft_substr(*str + index, 0, 1));
			index++;
		}
	}
	free(*str);
	*str = tmp;
}

void	expansion(t_token **token, t_env *env)
{
	int		size;

	size = token_list_size(*token);
	while (*token)
	{
		if ((*token)->type == WORD && (((*token)->prev
					&& (*token)->prev->type != REDIRECT_HERE_DOC) || size == 1))
		{
			expansion_env(&(*token)->str, env);
			if ((*token)->str[0] == '\0')
			{
				if (delete_token(token))
					continue ;
				else
					break ;
			}
			else
				remove_quote((*token)->str);
		}
		if (!(*token)->next)
			break ;
		*token = (*token)->next;
	}
	while ((*token) && (*token)->prev)
		*token = (*token)->prev;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:50:00 by jtakahas          #+#    #+#             */
/*   Updated: 2024/07/17 16:25:09 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word(char *line)
{
	char	*word;
	int		word_len;

	word_len = get_word_len(line);
	if (word_len == -1)
		return (NULL);
	word = ft_substr(line, 0, word_len);
	if (!word)
	{
		ft_putendl_fd("minishell: malloc failed", 2);
		return (NULL);
	}
	return (word);
}

char	*get_operator(char *line, t_token_type type)
{
	char	*operator;
	int		len;

	len = 1;
	if (type == REDIRECT_HERE_DOC || type == REDIRECT_APPEND)
		len = 2;
	operator = ft_substr(line, 0, len);
	if (!operator)
	{
		ft_putendl_fd("minishell: malloc failed", 2);
		return (NULL);
	}
	return (operator);
}

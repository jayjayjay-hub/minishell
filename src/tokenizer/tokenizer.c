/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:28:49 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/24 15:04:27 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	check_type(char *line)
{
	if (ft_strncmp(line, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(line, "<<", 2) == 0)
		return (REDIRECT_HERE_DOC);
	else if (ft_strncmp(line, ">>", 2) == 0)
		return (REDIRECT_APPEND);
	else if (ft_strncmp(line, "<", 1) == 0)
		return (REDIRECT_IN);
	else if (ft_strncmp(line, ">", 1) == 0)
		return (REDIRECT_OUT);
	else
		return (WORD);
}

int	get_word_len(char *line)
{
	int		len;
	char	quote;

	len = 0;
	while (line[len] && !is_metachar(line[len]) && !ft_isspace(line[len]))
	{
		if (is_quote(line[len]))
		{
			quote = line[len];
			len++;
			while (line[len] && line[len] != quote)
				len++;
			if (!line[len])
			{
				ft_putendl_fd("minishell: quote not closed", 2);
				return (-1);
			}
			len++;
		}
		else
			len++;
	}
	return (len);
}

int	add_token(t_token **token, char *line)
{
	t_token			*new;
	char			*token_str;
	t_token_type	type;

	type = check_type(line);
	if (type == WORD)
		token_str = get_word(line);
	else
		token_str = get_operator(line, type);
	if (!token_str)
		return (0);
	new = new_token(token_str, type, 0);
	free(token_str);
	token_add_back(token, new);
	return (ft_strlen(new->str));
}

bool	pipe_syntax_check(char *line)
{
	line = pass_space(line);
	if (line[0] == '|')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		error_status(1);
		return (false);
	}
	return (true);
}

t_token	*tokenize(char *line)
{
	t_token			*token;
	int				token_len;

	if (!pipe_syntax_check(line))
	{
		error_status(1);
		return (NULL);
	}
	token = NULL;
	while (*line)
	{
		line = pass_space(line);
		if (!*line || *line == '#')
			break ;
		token_len = add_token(&token, line);
		if (!token_len)
		{
			free_token(token);
			error_status(1);
			return (NULL);
		}
		line += token_len;
	}
	return (token);
}


#include "minishell.h"

int is_metachar(char c)
{
	return (c && ft_strchr("()<>", c));
}

int	is_quote(char c)
{
	return (c && ft_strchr("'\"", c));
}

int	is_word(const char *s)
{
	return (*s && !is_metachar(*s));
}

int	is_operator(const char *s)
{
	char	*const	operators[] = {"|", ">", ">>", "<", "<<"};
	size_t				i = 0;

	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (ft_memcmp(s, operators[i], ft_strlen(operators[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

t_token *word(char *line, int *quote)
{
	char	*tmp;
	char	*word;
	int		len;
	char	quote_char;

	len = 0;
	tmp = line;
	word = ft_calloc(1, ft_strlen(line) + 1);
	while (*line && !is_metachar(*line) && !ft_isspace(*line))
	{
		if (is_quote(*line))
		{
			quote_char = *line;
			*quote += 2;
			line++;
			while (*line && *line != quote_char)
				word[len++] = *line++;
			if (*line != quote_char)
				ft_error(NULL, NULL, "quote not closed", 1);
			line++;
		}
		else
			word[len++] = *line++;
	}
	return (new_token(word, WORD));
}

t_token	*operator(char *line)
{
	char	*const	operators[] = {"||", "&", "&&", "|", ">", ">>", "<"};
	size_t				i = 0;
	char				*op;

	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (ft_memcmp(line, operators[i], ft_strlen(operators[i])) == 0)
		{
			op = strdup(operators[i]);
			if (op == NULL)
				ft_error("strdup", NULL, strerror(errno), EXIT_FAILURE);
			return (new_token(op, OP));
		}
		i++;
	}
	ft_error(NULL, NULL, "invalid operator", 1);
	return (NULL);
}

int	get_token(t_token **token, char *line, t_token_type type)
{
	t_token	*new_token;
	char	*rest;
	int	quote;

	quote = 0;
	if (type == WORD)
		new_token = word(line, &quote);
	else if (type == OP)
		new_token = operator(line);
	add_back(token, new_token);
	return (ft_strlen(new_token->str) + quote);
}

t_token *tokenize(char *line)
{
	t_token *token = NULL;
	int			token_len;
	t_token_type	type;

	while (*line)
	{
		line = pass_space(line);
		if (!*line)
			break ;
		if (is_operator(line))
			type = OP;
		else if (is_word(line))
			type = WORD;
		else
			ft_error(NULL, NULL, "invalid token", 1);
		token_len = get_token(&token, line, type);
		line += token_len;
	}
	// print_token(token);
	return (token);
}

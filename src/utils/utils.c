/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jay <jay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:28:54 by kosnakam          #+#    #+#             */
/*   Updated: 2024/08/05 16:06:15 by jay              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_metachar(char c)
{
	return (c && ft_strchr("|<>", c));
}

int	is_quote(char c)
{
	return (c && ft_strchr("'\"", c));
}

int	is_single_quote(char c)
{
	return (c && c == '\'');
}

int	is_double_quote(char c)
{
	return (c && c == '\"');
}

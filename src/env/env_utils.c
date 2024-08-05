/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jay <jay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:29:19 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/20 17:31:35 by jay              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_alnum_under(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (true);
	return (false);
}

bool	is_al_under(char c)
{
	if (c == '_' || ft_isalpha(c))
		return (true);
	return (false);
}

bool	is_valid_identifier(char *str)
{
	int	index;

	index = 0;
	if (!str)
		return (false);
	if (!is_al_under(str[index]))
		return (false);
	index++;
	while (str[index] && is_alnum_under(str[index]))
		index++;
	if (str[index] && str[index] != '=')
		return (false);
	return (true);
}

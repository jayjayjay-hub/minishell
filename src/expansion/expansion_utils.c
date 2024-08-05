/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:42:07 by jtakahas          #+#    #+#             */
/*   Updated: 2024/07/24 14:51:25 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quote(char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				str[j++] = str[i++];
			i++;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

void	join_and_free(char **tmp, char *str)
{
	char	*tmp2;

	if (!str)
		tmp2 = ft_strjoin(*tmp, "\0");
	else
	{
		tmp2 = ft_strjoin(*tmp, str);
		free(str);
	}
	free(*tmp);
	*tmp = tmp2;
}

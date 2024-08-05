/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:42:55 by jtakahas          #+#    #+#             */
/*   Updated: 2024/07/22 18:38:05 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key_from_str(char *env_line)
{
	int		index;
	char	*key;

	index = 0;
	if (is_valid_identifier(env_line) == false)
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(env_line, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		error_status(1);
		return (NULL);
	}
	while (env_line && env_line[index] && env_line[index] != '=')
		index++;
	if (index == 0)
		return (NULL);
	key = malloc(sizeof(char) * (index + 1));
	if (!key)
		ft_error("malloc", "key", strerror(errno), EXIT_FAILURE);
	ft_strlcpy(key, env_line, index + 1);
	return (key);
}

char	*get_value_from_str(char *env_line)
{
	int		index;
	char	*value;

	index = 0;
	while (env_line && env_line[index] && env_line[index] != '=')
		index++;
	if (!env_line[index])
		return (NULL);
	index++;
	value = ft_strdup(env_line + index);
	if (!value)
		ft_error("ft_strdup", "value", strerror(errno), EXIT_FAILURE);
	return (value);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = NULL;
	i = 0;
	env = NULL;
	while (envp[i])
	{
		new = new_env(envp[i], true, NULL);
		env_add_back(new, &env);
		i++;
	}
	return (env);
}

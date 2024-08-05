/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:25:38 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/24 15:27:35 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	error_cd(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	perror(path);
	error_status(1);
	free(path);
	return (true);
}

static char	*prev_path(char *path)
{
	int		i;
	int		j;
	char	*new_path;

	i = 0;
	j = 0;
	if (!path)
		return (NULL);
	while (path[i])
		i++;
	while (path[i] != '/')
		i--;
	new_path = (char *)malloc(sizeof(char) * (i + 1));
	if (!new_path)
		return (NULL);
	while (j < i)
	{
		new_path[j] = path[j];
		j++;
	}
	new_path[j] = '\0';
	return (new_path);
}

static bool	control_env_cd(t_env **env, char *path)
{
	char	*old;
	char	*home;

	if (path && chdir(path) == -1)
		return (error_cd(path));
	old = get_env_value("PWD", *env);
	home = getcwd(NULL, 0);
	edit_env_value("OLDPWD", old, env);
	edit_env_value("PWD", home, env);
	error_status(0);
	free(path);
	free(home);
	free(old);
	return (true);
}

bool	do_cd(t_token *token, t_env **env, char *path)
{
	char	*tmp;

	if (token->next)
		return (ft_putendl_fd("minishell: cd: too many arguments", 2),
			error_status(1), true);
	else if (!ft_strncmp(token->str, "-", 1) && ft_strlen(token->str) == 1)
	{
		path = get_env_value("OLDPWD", *env);
		ft_putendl_fd(path, 1);
	}
	else if (!ft_strncmp(token->str, "~", 1) && ft_strlen(token->str) == 1)
		path = get_env_value("HOME", *env);
	else if (!ft_strncmp(token->str, ".", 1) && ft_strlen(token->str) == 1)
		path = get_env_value("PWD", *env);
	else if (!ft_strncmp(token->str, "..", 2) && ft_strlen(token->str) == 2)
	{
		tmp = getcwd(NULL, 0);
		if (!(!ft_strncmp(tmp, "/", 1) && ft_strlen(tmp) == 1))
			path = prev_path(tmp);
		free(tmp);
	}
	else
		path = ft_strdup(token->str);
	return (control_env_cd(env, path));
}

bool	builtin_cd(t_token *token, t_env **env)
{
	char	*old;
	char	*path;
	char	*home;

	path = NULL;
	if (!token->next)
	{
		path = get_env_value("HOME", *env);
		if (!path)
			return (ft_putendl_fd("cd: HOME not set", 2),
				error_status(1), true);
		else if (path[0] == '\0')
			return (free(path), true);
		if (chdir(path) == -1)
			return (ft_putstr_fd("cd: ", 2),
				perror(path), error_status(1), free(path), true);
		old = get_env_value("PWD", *env);
		edit_env_value("OLDPWD", old, env);
		home = getcwd(NULL, 0);
		edit_env_value("PWD", home, env);
		return (free(path), free(old), free(home), true);
	}
	token = token->next;
	return (do_cd(token, env, path));
}

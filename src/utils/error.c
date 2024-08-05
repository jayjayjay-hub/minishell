/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:27:04 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/22 18:36:05 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *cmd, char *target, char *main_message, int status)
{
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (target)
	{
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(main_message, 2);
	if (status)
		exit(status);
}

void	handle_eof(char *line)
{
	write(2, "exit\n", 5);
	if (line)
		free(line);
	exit(error_status(PRINT_ERROR));
}

int	error_status(int error_code)
{
	static int	status;

	if (error_code < 0)
		return (status);
	status = error_code;
	return (status);
}

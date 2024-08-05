/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:28:08 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/22 20:16:59 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	(void)sig;
	error_status(130);
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	register_signal(void)
{
	t_sig	int_sa;
	t_sig	quit_sa;

	int_sa.sa_handler = signal_handler;
	sigemptyset(&int_sa.sa_mask);
	sigaddset(&int_sa.sa_mask, SIGINT);
	int_sa.sa_flags = SA_RESTART;
	quit_sa.sa_handler = SIG_IGN;
	sigemptyset(&quit_sa.sa_mask);
	sigaddset(&quit_sa.sa_mask, SIGQUIT);
	quit_sa.sa_flags = 0;
	sigaction(SIGINT, &int_sa, NULL);
	sigaction(SIGQUIT, &quit_sa, NULL);
}

void	sigint_handler_exit(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_DFL);
	ft_putendl_fd("", 1);
	rl_on_new_line();
	kill(0, SIGINT);
}

void	sig_heredoc(void)
{
	t_sig	sa;

	sa.sa_handler = sigint_handler_exit;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

void	sig_stop(void)
{
	t_sig	stop_sa;

	stop_sa.sa_handler = SIG_IGN;
	sigemptyset(&stop_sa.sa_mask);
	sigaddset(&stop_sa.sa_mask, SIGINT);
	stop_sa.sa_flags = 0;
	sigaction(SIGINT, &stop_sa, NULL);
}

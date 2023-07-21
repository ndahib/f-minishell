/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 22:36:18 by yraiss            #+#    #+#             */
/*   Updated: 2023/07/21 01:58:21 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    handle_sigint(int sig)
{
	(void) sig;
	write(2, "\n", 1);
    rl_replace_line("",0);
	rl_on_new_line();
    rl_redisplay();
	signal(SIGINT, handle_sigint);
}

void	handle_endoffile(int sig)
{
	(void) sig;
	exit(0);
}

void	handle_sigquit(int sig)
{
	(void) sig;
}

void signals()
{
	signal(SIGINT, handle_sigint);
	signal(EOF, handle_endoffile);
	signal(SIGQUIT, handle_sigquit);
}
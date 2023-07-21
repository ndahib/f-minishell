/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyser_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:11:01 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/21 15:38:50 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file_name(char *token, char *name)
{
	if (ft_strncmp(">", token, 2) == 0)
	{
		if (ft_strncmp(">>", name, 3) == 0 || ft_strncmp("<", name, 2) == 0
			|| ft_strncmp("|", name, 2) == 0)
			return (1);
	}
	if (ft_strncmp(">>", token, 3) == 0)
	{
		if (ft_strncmp(">", name, 2) == 0 || ft_strncmp("<", name, 2) == 0 
		|| (ft_strncmp(">>", name, 3) == 0) || ft_strncmp("|", name, 2) == 0)
			return (1);
	}
	if (ft_strncmp("<", token, 2) == 0)
	{
		if (ft_strncmp("<<", name, 2) == 0 || ft_strncmp(">", name, 2) == 0
			|| ft_strncmp("|", name, 2) == 0)
			return (1);
	}
	if (ft_strncmp("<<", token, 2) == 0)
	{
		if (ft_strncmp("<", name, 2) == 0 || ft_strncmp(">", name, 2) == 0
			|| ft_strncmp("<<", name, 3) == 0 || ft_strncmp("|", name, 2) == 0)
			return (1);
	}
	return (0);
}

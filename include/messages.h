/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:14:38 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/23 21:30:30 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define ALLOC_ERR		"Faillure to allocate memory\n"
# define PARSE_ERR		"munishell: parse error near :"
# define LIST_NULL		"the linked list is NULL\n"
# define PWD_ERROR		"Faillure to quires the current directory\n"
# define CD_ERROR		"Directory not Found\n"
# define CD_SUCCS		"SUCSSES to change directory\n"
# define ENV_ERR		"No such file or directory\n"
# define EXPORT_ER 		"minishell :export: "
# define EXPORT_VAR		"_=/Users/ndahib/Desktop/minishell1/./minishell"
# define OUT_OF_RANGE	"bash: exit: %s: numeric argument required\n"

//////////////////FUNCTIONS_THAT_PRINT////////////////////////

void	printf_double_pointer(char **arr);

#endif
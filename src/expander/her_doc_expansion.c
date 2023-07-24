/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:42:13 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/23 19:32:15 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//========check_if_quotes-exist================================================
int	check_del(char *del)
{
	while (*del != '\0')
	{
		if (*del == '"' || *del == '\'')
			return (1);
		del++;
	}
	return (0);
}

//=======remove_quotes_from_del================================================
char	*remove_quotes(char *del)
{
	char	*new_del;

	new_del = "";
	while (*del != '\0')
	{
		if (*del == '"' || *del == '\'')
			del++;
		new_del = ft_joinchar(new_del, *del);
		if (*del != '\0')
			del++;
	}
	return (new_del);
}

//==========expand_the_buff_of_herdoc==========================================
char	*expand_her_doc(char *buff, t_env *env)
{
	char	*new_buff;

	new_buff = "";
	while (*buff != '\0')
	{
		if (*buff == '$')
			obtain_value(env, &new_buff, &buff);
		new_buff = ft_joinchar(new_buff, *buff);
		buff++;
	}
	return (new_buff);
}

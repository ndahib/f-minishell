/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:49:24 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/29 15:56:02 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_varibale(t_env *lst, char *var)
{
	t_env	*head;
	int		len;

	head = lst;
	if (head == NULL)
		return (NULL);
	while (head != NULL)
	{
		len = len_of_word(head->env, '=') - 1;
		if (ft_strncmp(head->env, var, len) == 0
			&& ft_strncmp(head->env, var, len_of_word(var, '\0') - 1) == 0)
			return (head->env);
		head = head->next;
	}
	return (NULL);
}

int	lenght_of_value(char *var)
{
	int	count;

	count = 0;
	while (*var != '=')
		var++;
	var++;
	while (*var != '\0')
	{
		count++;
		var++;
	}
	return (count);
}

// char	*obtain_his_value(char *env_var)
// {
// 	int		len;
// 	int		i;
// 	char	*value;

// 	i = -1;
// 	len = lenght_of_value(env_var);
// 	value = ft_calloc(len + 1, sizeof(char));
// 	while (*env_var != '=')
// 		env_var++;
// 	env_var++;
// 	while (++i < len)
// 	{
// 		value[i] = *env_var;
// 		env_var++;
// 	}
// 	return (value);
// }

char	*my_getenv(t_env *lst, char *variable)
{
	char	*env_var;
	char	**split_var;
	char	*value;

	if (lst == NULL)
		return (NULL);
	if (!variable)
		return (NULL);
	value = NULL;
	env_var = search_varibale(lst, variable);
	if (env_var)
	{
		split_var = ft_split(env_var, '=');
		if (split_var[1] != NULL)
			value = ft_strdup(split_var[1]);
		else
			value = NULL;
		free_double_pointer(split_var);
	}
	return (value);
}

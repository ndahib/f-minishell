/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:49:24 by ndahib            #+#    #+#             */
/*   Updated: 2023/06/20 09:27:53 by ndahib           ###   ########.fr       */
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

char	*obtain_his_value(char *env_var)
{
	int		len;
	int		i;
	char	*value;

	i = -1;
	len = lenght_of_value(env_var);
	value = ft_calloc(len + 1, sizeof(char));
	while (*env_var != '=')
		env_var++;
	env_var++;
	while (++i < len)
	{
		value[i] = *env_var;
		env_var++;
	}
	value[i] = '\0';
	return (value);
}

char	*my_getenv(t_env *lst, char *variable)
{
	char	*env_var;

	if (lst == NULL)
		return (NULL);
	if (!variable)
		return (NULL);
	env_var = search_varibale(lst, variable);
	if (env_var)
	{
		return (obtain_his_value(env_var));
	}
	return (NULL);
}

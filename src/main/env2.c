/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:31:00 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/29 15:00:47 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_variable(char *token)
{
	if (ft_isalpha(*token) == 0 && *token != '_')
		return (1);
	token++;
	while (*token != '=' && *token != '\0')
	{
		if (ft_isalpha((int)*token) == 0)
			return (1);
		token++;
	}
	return (0);
}

char	*skip_quotes(char *token, char sep)
{
	char	*result;
	int		len;
	int		i;

	len = ft_strlen(token) - 2;
	result = malloc(len + 1 * sizeof(char));
	i = 0;
	while (i < len)
	{
		if (*token == sep)
			token++;
		result[i] = *token;
		i++;
		token++;
	}
	result[i] = '\0';
	return (result);
}

int	check_if_quotes_exist(char **token)
{
	int		rsl;
	char	sep;

	sep = '\0';
	if (ft_strchr(*token, '\'') != NULL || ft_strchr(*token, '"') != NULL)
	{
		if (ft_strchr(*token, '"') != NULL)
			sep = '"';
		else
			sep = '\'';
		*token = skip_quotes(*token, sep);
	}
	rsl = check_variable(*token);
	return (rsl);
}

int	check_if_exist(t_env **lst, char **variable)
{
	t_env	*tmp;
	int		len1;
	int		len2;

	tmp = *lst;
	if (*lst == NULL || lst == NULL)
	{
		ft_putstr_fd(LIST_NULL, 2);
		return (-1);
	}
	while (tmp != NULL)
	{
		len1 = len_of_word(tmp->env, '=') - 1;
		len2 = len_of_word(variable[0], '\0') - 1;
		if (ft_strncmp(tmp->env, variable[0], len1) == 0
			&& ft_strncmp(tmp->env, variable[0], len2) == 0)
		{
			free(tmp->env);
			variable[0] = ft_joinchar(variable[0], '=');
			tmp->env = ft_strjoin(ft_strdup(variable[0]), variable[1]);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

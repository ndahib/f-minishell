/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:21:33 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/21 15:26:54 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

//*******************FUNCTIONS********************//

char	**tokeniser(char *line);
char	*skip_space(char *line);
int 	check_syntax_err(char **tokens);
int		len_of_word(const char *line, char sep);
char	*quotes(char **line, char sep);
int		token_nbr(char **token);
int		check_file_name(char *token, char *name);

//*********************ENVIR********************//
int		check_if_quotes_exist(char **token);
#endif
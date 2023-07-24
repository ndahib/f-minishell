/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:21:33 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/24 00:38:02 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

//*********************************FUNCTIONS***********************************
char	**tokeniser(char *line);
char	*skip_space(char *line);
int		token_nbr(char **token);
int		len_of_word(const char *line, char sep);
int		check_file_name(char *token, char *name);

//*********************************SYNTAX_ERROR_FUNCTIONS**********************
int		check_syntax_err(char **tokens);
char	*quotes(char **line, char sep);
int		check_if_quotes_exist(char **token);
int		check_syntax_error(char **tokens, char quot);

#endif
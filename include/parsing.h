/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:29:54 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/30 20:00:45 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//***********************************TYPES_OF_FILES****************************
# define INPRED	3
# define OUTRED	4
# define APP	5

//************************************ENV_LIST*********************************
typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}	t_env;

//************************************FILES_LIST*******************************
typedef struct s_files		t_files;
struct s_files
{
	char	*file;
	int		type;
	t_files	*next;
};
//************************************COMMAND_STRUCT***************************
typedef struct s_simple_cmd	t_simple_cmd;
struct s_simple_cmd
{
	char			*cmd;
	char			*path;
	char			**arg;
	t_files			*files;
	int				fd;
	t_simple_cmd	*next;
};
//////////////////////////////////////FUNCTIONS////////////////////////////////

//***********************************PARSING***********************************
t_simple_cmd	*parse_simple_cmd(t_env *env_lst, char **token);
void			add_at_end_cmd(t_simple_cmd **head, t_simple_cmd *node);
t_files			*obtain_files(char ***token, t_simple_cmd **simple, t_env *env);

//***********************************EXPAND************************************
int				len_of_var(char *var);
void			print_lst(t_files *lst);
char			*name_of_file(char *token);
char			**expander(t_env *env, char **arg);
char			*my_getenv(t_env *lst, char *varibale);
void			join_cursor(char **new_arg, char *cursor);
char			*obtain_path(char *command, t_env *env_list);
int				check_if_exist(t_env **lst, char **variable);
void			add_at_end_export(t_env ***head, t_env *node);
void			join_and_increment(char **new_arg, char **arg);
void			expand_exit_status(char **new_arg, char **arg, int flag);
void			expande_inside_quotes(char **new_arg, char **arg, t_env *env);
//***********************************HER_DOC EXPAND****************************
int				check_del(char *del);
char			*remove_quotes(char *del);
int				her_doc(char *del, t_env *env);
char			*expand_her_doc(char *buff, t_env *env);
void			obtain_value(t_env *env, char **new_arg, char **arg);
void			print_lst(t_files *lst);
void			handle_herdoc(int sig);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:29:54 by ndahib            #+#    #+#             */
/*   Updated: 2023/07/17 23:33:22 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define INPUT	0
# define OUTPUT	1
# define ERR	2
# define INPRED	3
# define OUTRED	4
# define APP	5
# define HERDOC 6

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}	t_env;

typedef struct s_files		t_files;
struct s_files
{
	char	*file;
	int		type;
	t_files	*next;
};

typedef struct s_simple_cmd	t_simple_cmd;
struct s_simple_cmd
{
	char			*cmd;
	char			*path;
	char			**arg;
	t_files			*files;
	t_simple_cmd	*next;
};

//*******************FUNCTIONS********************//
t_env			*handle_env(char **env);
t_env			*create_node(char *env);
t_files			*obtain_files(char ***token);
t_simple_cmd	*parse_simple_cmd(t_env *env_lst, char **token);
/////////////////////////////////////////////////////
int				len_of_var(char *var);
void			print_lst(t_files *lst);
char			**expander(t_env *env, char **arg);
void			add_at_end_export(t_env ***head, t_env *node);
char			*my_getenv(t_env *lst, char *varibale);
char			*obtain_path(char *command, t_env *env_list);
int				check_if_exist(t_env **lst, char **variable);
////////////////////////ADD_NODE////////////////////////////
void			add_at_end_cmd(t_simple_cmd **head, t_simple_cmd *node);
/////////////////////////FREEE UTILS ///////////////////////////////////
void			free_double_pointer(char **pointer);
#endif
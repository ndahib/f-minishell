/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:52:25 by yraiss            #+#    #+#             */
/*   Updated: 2023/07/24 17:26:58 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

//*******************STRCUT****************************************************
typedef struct s_pipe_files
{
	int	pipe_fd[2];
	int	input_fd;
	int	i;
}	t_pipe_files;

//*******************FUNCTIONS*************************************************

int		execute_commands(t_simple_cmd *cmnd, t_env **env);
int		is_built_ins(t_env **lst, t_simple_cmd *cmd);
int		check_is_built_ins(char *cmd);
int		redirections(t_files *cmnd);
int		get_number_of_cmds(t_simple_cmd *cmnd);
char	**convert_env_to_array(t_env *env);

//*******************BUILTINS**************************************************
void	new_pwd(t_env **env);
void	old_pwd(t_env **env);
void	new_pwd(t_env **env);
void	old_pwd(t_env **env);
void	my_pwd(void);
void	my_exit(char **arg);
void	my_echo(char **arg);
void	my_env(t_env **lst);
void	my_export(t_env ***lst, char **args);
void	unset_variable(t_env ***lst, char *arg);
int		my_cd(t_simple_cmd *cmnd, t_env **env);
int		run_built_ins(t_env **env, t_simple_cmd *cmd);

//*******************UTILS*****************************************************
int		check_is_nbr(char *arg);
int		count_env(t_env *envr);
int		count_args(char **args);
void	my_free1(char *p, char **args);
char	**convert_env_to_array(t_env *env);
int		get_number_of_cmds(t_simple_cmd *cmnd);
char	*ft_strjoin_line(char *s1, char *s2, int len2);
void	ft_strcpy(char *dst, const char *stash, int start, int len);

//*******************Get Next line*********************************************
char	*get_next_line(int fd);

//************************CREATING CHILD***************************************
void	dup_close(int fd);
void	dup_fd(int *pipe, int fd);
void	wait_childs(int nbr);
int		check_redir(t_files *files);
void	copy_input_to_fd(int *input_fd, int *pipe_fd);
void	create_child(t_simple_cmd *one_cmd, char **env);
void	execute_cmd(t_simple_cmd *cmd, char **env_arr);
void	create_childs(t_simple_cmd *cmd, t_env **env, t_pipe_files *var);
//**************************REDIRECTION****************************************
int		in_redirection(char *file);
int		out_redirection(char *file);
int		append_redirection(char *file);

#endif
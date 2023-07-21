/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:52:25 by yraiss            #+#    #+#             */
/*   Updated: 2023/07/21 23:27:22 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

int	exit_status;
//*******************FUNCTIONS********************//

int		execute_commands(t_simple_cmd *cmnd, t_env **env);
int		is_built_ins(t_env **lst, t_simple_cmd *cmd);
int     check_is_built_ins(char *cmd);
int		redirections(t_files *cmnd);
int     get_number_of_cmds(t_simple_cmd *cmnd);
char	**convert_env_to_array(t_env *env);

//*******************BUILTINS********************//
void	new_pwd(t_env **env);
void	old_pwd(t_env **env);
//*******************UTILS********************//

int		check_is_nbr(char *arg);
int		count_env(t_env *envr);
int		count_args(char **args);
void	my_free1(char *p, char **args);
char	**convert_env_to_array(t_env *env);
int		get_number_of_cmds(t_simple_cmd *cmnd);
char	*ft_strjoin_line(char *s1, char *s2, int len2);
void	ft_strcpy(char *dst, const char *stash, int start, int len);

//*******************Get Next line********************//
char	*get_next_line(int fd);


#endif
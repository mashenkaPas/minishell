/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_ls.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpas <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 19:02:43 by mpas              #+#    #+#             */
/*   Updated: 2019/03/16 19:28:42 by mpas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "../b_printf/libftprintf.h"
# include "../libft/libft.h"
# define LSH_RL_BUFSIZE 1024
# define LSH_TOK_BUFSIZE 64
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"
# define L_RED     "\x1b[1;31m"
# define L_GREEN   "\x1b[1;32m"
# define L_YELLOW  "\x1b[1;33m"
# define L_BLUE    "\x1b[1;34m"
# define L_MAGENTA "\x1b[1;35m"
# define L_CYAN    "\x1b[1;36m"

typedef struct	s_node
{
	char			*type;
	char			*data;
	struct s_node	*next;
}				t_node;

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

void			delete_double_pointer(char **obj);
t_env			*g_ptm;
extern char		*g_builtin_str[];
extern int		(*g_builtin_func[]) (char **);
int				lsh_cd(char **args);
int				lsh_help(char **args);
int				lsh_exit(char **a);
int				lsh_setenv(char **args);
int				lsh_unsetenv(char **name);
int				env(char **args);
int				lsh_num_builtins();
void			add_to_env(char *key, char *value);
void			print_env();
void			create_env();
char			*search_by_key(char *key);
void			replace_value(char *key, char *new_value);
void			true_setenv(char *key, char *value);
void			free_node(t_env *list);
void			delete_list_env(char *key);
char			*ft_update(char *str, char *update);
int				ft_list_size_env (t_env *root);
char			**list_to_arr_env(t_env *list);
int				ft_list_size(t_node *root);
char			**list_to_arr(t_node *list);
char			*valid_tilda(char *type, char *data);
char			*manage_dollar(char *type, char *data);
t_node			*add_to_list(t_node *list, char *type, char *data);
int				ft_checker (char *str);
char			**split2(char *str);
char			*lsh_read_line(void);
void			print_command(char *path, char **argv);
int				check_if_path_exists(char **p, char *path, char **args);
int				find_command(char **args);
void			find_command_in_dirs(char **d_comm);
int				lsh_execute(char **args);
void			lsh_loop(void);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpas <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:21:01 by mpas              #+#    #+#             */
/*   Updated: 2019/03/17 21:08:16 by mpas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes//minishell.h"

void		print_command(char *path, char **argv)
{
	pid_t	pid;
	char	**execve_helper;

	execve_helper = list_to_arr_env(g_ptm);
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, argv, execve_helper) == -1)
			b_printf(L_RED "minishell: %s: command not found\n" RESET, path);
		exit(-1);
	}
	else if (pid == -1)
	{
		b_printf(L_RED "Unable to fork process\n" RESET);
		exit(-1);
	}
	if (pid >= 1)
		wait(&pid);
	delete_double_pointer(execve_helper);
}

int			check_if_path_exists(char **p, char *path, char **args)
{
	int		i;

	i = -1;
	while (p[++i])
	{
		ft_strclr(path);
		path = ft_strcat(path, p[i]);
		(args[0][0] == '/') ? 0 : ft_strcat(path, "/");
		path = ft_strcat(path, args[0]);
		if (access(path, F_OK) != -1)
		{
			print_command(path, args);
			i = -100;
			break ;
		}
	}
	if (i == -100)
		return (1);
	return (-1);
}

int			find_command(char **args)
{
	char	**p;
	char	*path;

	if (!ft_strcmp("EMPTY", search_by_key("PATH")))
		return (-1);
	p = ft_strsplit(search_by_key("PATH"), ':');
	path = ft_strnew(4000);
	if (check_if_path_exists(p, path, args) == 1)
	{
		ft_strdel(&path);
		delete_double_pointer(p);
		return (0);
	}
	ft_strdel(&path);
	delete_double_pointer(p);
	return (-1);
}

void		find_command_in_dirs(char **d_comm)
{
	if (access(d_comm[0], F_OK) != -1)
		print_command(d_comm[0], d_comm);
	else if (find_command(d_comm) == -1)
		b_printf(L_RED "minishell: %s: command not found\n" RESET, d_comm[0]);
}

int			lsh_execute(char **args)
{
	int	i;

	i = 0;
	if (args[0] == NULL)
		return (1);
	while (i < 6)
	{
		if (ft_strcmp(args[0], g_builtin_str[i]) == 0)
			return (*g_builtin_func[i])(args);
		i++;
	}
	find_command_in_dirs(args);
	return (1);
}

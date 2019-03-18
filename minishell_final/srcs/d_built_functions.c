/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_built_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpas <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:07:12 by mpas              #+#    #+#             */
/*   Updated: 2019/03/16 18:19:38 by mpas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes//minishell.h"

char *g_builtin_str[] = {"cd", "exit", "help", "env", "setenv", "unsetenv"};

int (*g_builtin_func[])(char **) = {&lsh_cd, &lsh_exit, &lsh_help, &env,
	&lsh_setenv, &lsh_unsetenv};

int	env(char **args)
{
	print_env();
	return (1);
	free(args);
}

int	lsh_unsetenv(char **key)
{
	if (ft_strcmp(search_by_key(key[1]), "EMPTY") != 0)
		delete_list_env(key[1]);
	return (1);
}

int	lsh_setenv(char **args)
{
	char	**tmp;

	if (!args[1])
		return (1);
	if (ft_strchr(args[1], '=') == NULL)
	{
		if (args[2])
			true_setenv(args[1], args[2]);
		else
			true_setenv(args[1], NULL);
	}
	else
	{
		tmp = ft_strsplit(args[1], '=');
		true_setenv(tmp[0], tmp[1]);
		delete_double_pointer(tmp);
	}
	return (1);
}

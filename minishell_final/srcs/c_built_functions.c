/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_built_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpas <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:31:04 by mpas              #+#    #+#             */
/*   Updated: 2019/03/17 21:06:43 by mpas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes//minishell.h"

void	delete_double_pointer(char **obj)
{
	char **tmp;

	tmp = obj;
	while (*obj)
		ft_strdel(&(*obj++));
	ft_memdel((void**)&tmp);
}

int		lsh_exit(char **args)
{
	return (0);
	free(args);
}

int		lsh_cd(char **args)
{
	char c_pwd[64];
	char n_pwd[64];

	if (args[1] == NULL)
	{
		getwd(c_pwd);
		replace_value("OLDPWD", ft_strdup(c_pwd));
		if (chdir(search_by_key("HOME")) != 0)
			perror("lsh");
	}
	else
	{
		getwd(c_pwd);
		if (!ft_strcmp("-", args[1]) && chdir(search_by_key("OLDPWD")) != 0)
			perror("lsh");
		else if (!ft_strcmp("-", args[1]))
			b_printf("%s\n", getwd(n_pwd));
		else if (chdir(args[1]) != 0)
			perror("lsh");
		replace_value("OLDPWD", ft_strdup(c_pwd));
		getwd(n_pwd);
		replace_value("PWD", ft_strdup(n_pwd));
	}
	return (1);
}

int		lsh_help(char **args)
{
	int i;

	i = 0;
	b_printf(L_BLUE "You can use following commands:\n" RESET);
	while (i < 6)
	{
		b_printf(L_MAGENTA "- %s\n" RESET, g_builtin_str[i]);
		i++;
	}
	return (1);
}

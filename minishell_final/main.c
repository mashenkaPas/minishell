/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpas <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 16:11:00 by mpas              #+#    #+#             */
/*   Updated: 2019/03/17 21:03:28 by mpas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes//minishell.h"

void	lstdel_env(t_env **list)
{
	t_env	*temp;

	if ((*list))
	{
		temp = (*list)->next;
		(*list)->next = NULL;
		ft_strdel(&(*list)->value);
		ft_strdel(&(*list)->key);
		ft_memdel((void**)&(*list));
		lstdel_env(&(temp));
	}
}

void	lsh_loop(void)
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		write(1, "supershell> ", 12);
		get_next_line(0, &line);
		args = split2(line);
		status = lsh_execute(args);
		ft_strdel(&line);
		delete_double_pointer(args);
	}
}

int		main(void)
{
	create_env();
	lsh_loop();
	return (0);
}

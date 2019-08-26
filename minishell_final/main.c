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

#define PROMPT "supershell> "

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

int 	lsh_loop(void)
{
	char	*line;
	char	**args;
	int		status;
	int   result;

	status = 1;
	while (status)
	{
		write(1, PROMPT, sizeof(PROMPT) - 1);

		result = get_next_line(0, &line);
		if (result == 0)
			return 0;
		else if (result == -1)
			return -1;

		args = split2(line);
		status = lsh_execute(args);
		ft_strdel(&line);
		delete_double_pointer(args);
	}
	return status;
}

int		main(void)
{
	create_env();
	return lsh_loop();
}

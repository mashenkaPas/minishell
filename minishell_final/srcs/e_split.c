/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpas <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:20:34 by mpas              #+#    #+#             */
/*   Updated: 2019/03/17 21:13:38 by mpas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes//minishell.h"

t_node	*split_helper1(char **str, t_node *list)
{
	char	**args;
	int		i;
	int		j;
	int		k;
	char	*strspac;

	i = 0;
	k = 0;
	j = ft_checker(*str);
	strspac = ft_strnew(j);
	strspac = ft_strncpy(strspac, *str, j);
	while (strspac[k])
	{
		if (ft_ispace(strspac[k]))
			strspac[k] = ' ';
		k++;
	}
	args = ft_strsplit(strspac, ' ');
	while (args[i])
		list = add_to_list(list, "space", args[i++]);
	ft_strdel(&strspac);
	delete_double_pointer(args);
	*str = *str + j;
	return (list);
}

void	split_error(void)
{
	b_printf("error");
	exit(1);
}

t_node	*split_helper2(char **str, t_node *list, int j)
{
	char *strqer;

	strqer = ft_strnew(j - 1);
	strqer = ft_strncpy(strqer, *str + 1, j - 1);
	list = add_to_list(list, "special", strqer);
	ft_strdel(&strqer);
	*str = *str + j + 1;
	return (list);
}

void	lstdel(t_node **list)
{
	t_node	*temp;

	if ((*list))
	{
		temp = (*list)->next;
		(*list)->next = NULL;
		ft_strdel(&(*list)->data);
		ft_strdel(&(*list)->type);
		ft_memdel((void**)&(*list));
		lstdel(&(temp));
	}
}

char	**split2(char *str)
{
	t_node	*list;
	int		j;
	char	**new;

	list = NULL;
	while (*str)
	{
		if (*str && *str != 34 && *str != 39)
			list = split_helper1(&str, list);
		if (*str == 34 || *str == 39)
		{
			j = 1;
			while (str[j] && (str[j] != *str))
				j++;
			if (!str[j])
				split_error();
			if (*str == str[j])
				list = split_helper2(&str, list, j);
		}
	}
	new = list_to_arr(list);
	lstdel(&list);
	return (new);
}

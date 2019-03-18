/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_env_funcioins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpas <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:30:35 by mpas              #+#    #+#             */
/*   Updated: 2019/03/17 21:09:04 by mpas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes//minishell.h"

void	free_node(t_env *list)
{
	ft_strdel(&list->key);
	ft_strdel(&list->value);
	list->next = NULL;
	ft_memdel((void**)&list);
}

void	delete_list_env(char *key)
{
	t_env		*head;
	t_env		*tmp;

	head = g_ptm;
	if (ft_strcmp(g_ptm->key, key) == 0)
	{
		tmp = g_ptm;
		g_ptm = g_ptm->next;
		free_node(tmp);
		return ;
	}
	while (head && head->next && ft_strcmp(head->next->key, key))
		head = head->next;
	if (head && head->next && !ft_strcmp(head->next->key, key))
	{
		tmp = head->next;
		head->next = head->next->next;
		free_node(tmp);
	}
	else if (head && !ft_strcmp(head->key, key))
	{
		tmp = head;
		head->next = NULL;
		free_node(tmp);
	}
}

char	*search_by_key(char *key)
{
	t_env *current_node;

	current_node = g_ptm;
	if (!key)
		return ("EMPTY");
	while ((current_node != NULL) && (ft_strcmp(current_node->key, key) != 0))
		current_node = current_node->next;
	if (current_node == NULL)
		return ("EMPTY");
	else
		return (current_node->value);
}

void	replace_value(char *key, char *new_value)
{
	t_env *current_node;

	current_node = g_ptm;
	while ((current_node != NULL) && (ft_strcmp(current_node->key, key) != 0))
		current_node = current_node->next;
	if (!current_node)
		return ;
	if (new_value)
	{
		ft_strdel(&current_node->value);
		current_node->value = ft_strdup(new_value);
	}
	else
		current_node->value = ft_strdup("");
	ft_strdel(&new_value);
}

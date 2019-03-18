/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_manage_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpas <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:24:40 by mpas              #+#    #+#             */
/*   Updated: 2019/03/16 18:27:17 by mpas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes//minishell.h"

char	*manage_dollar(char *type, char *data)
{
	char	*newdata;
	int		i;

	i = 0;
	if (*data && ft_strcmp(type, "space") == 0 && data[0] == '$')
	{
		data++;
		if (*data)
		{
			if (ft_strcmp(search_by_key(data), "EMPTY"))
			{
				newdata = ft_strdup(search_by_key(data));
				return (newdata);
			}
			else
				return ("there is no env like this");
		}
		else
			return ("$");
	}
	return (ft_strdup(data));
}

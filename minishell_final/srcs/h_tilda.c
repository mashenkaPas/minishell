/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_tilda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpas <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:27:25 by mpas              #+#    #+#             */
/*   Updated: 2019/03/16 18:28:36 by mpas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes//minishell.h"

char	*valid_tilda(char *type, char *data)
{
	char	*newdata;
	char	*tmp;

	if (*data && ft_strcmp(type, "space") == 0 && data[0] == '~')
	{
		data++;
		tmp = ft_strdup(search_by_key("HOME"));
		if (*data)
			newdata = ft_strjoin(tmp, data);
		else
			newdata = ft_strjoin(tmp, "/");
		ft_strdel(&tmp);
		return (newdata);
	}
	return (ft_strdup(data));
}

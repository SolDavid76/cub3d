/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:14:49 by djanusz           #+#    #+#             */
/*   Updated: 2023/09/11 16:35:10 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_strslen(char **strs)
{
	int	i;

	if (!strs)
		return (0);
	i = 0;
	while (strs[i])
		i++;
	return (i);
}

char	**ft_strsdup(char **strs)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (ft_strslen(strs) + 1));
	if (!res)
		ft_exit("NOT ENOUGH MEMORY\n");
	i = -1;
	while (strs[++i])
		res[i] = ft_strdup(strs[i]);
	res[i] = NULL;
	return (res);
}

int	ft_strschr(char **strs, char c)
{
	int	i;

	if (!strs)
		return (0);
	i = 0;
	while (strs[i])
	{
		if (ft_strchr(strs[i], c))
			return (i);
		i++;
	}
	return (0);
}

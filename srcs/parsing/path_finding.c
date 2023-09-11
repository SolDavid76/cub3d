/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:04:44 by djanusz           #+#    #+#             */
/*   Updated: 2023/09/11 16:35:02 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	path_finding_start(char **map)
{
	int	res;
	int	i;
	int	j;

	i = -1;
	res = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' ')
			{
				if (map[i][j] == 'N' || map[i][j] == 'S'
					|| map[i][j] == 'E' || map[i][j] == 'W')
				{
					map[i][j] = 'X';
					res++;
				}
				else
					return (-1);
			}
		}
	}
	return (res);
}

int	path_finding_aux_check(char **map, int y, int x)
{
	return (map[y][x] != '1' && map[y][x] != 'X');
}

int	path_finding_aux(char **map, int x, int y)
{
	int	res;
	int	i;

	i = 1;
	res = 0;
	while (x + i < ft_strlen(map[y]) && path_finding_aux_check(map, y, x + 1))
		map[y][x + i++] = 'X';
	res += i - 1;
	i = 1;
	while (x - i >= 0 && path_finding_aux_check(map, y, x - 1))
		map[y][x - i++] = 'X';
	res += i - 1;
	i = 1;
	while (y + i < ft_strslen(map) && path_finding_aux_check(map, y + 1, x))
		map[y + i++][x] = 'X';
	res += i - 1;
	i = 1;
	while (y - i >= 0 && path_finding_aux_check(map, y - 1, x))
		map[y - i++][x] = 'X';
	res += i - 1;
	return (res);
}

int	path_finding_verif(char **map)
{
	int	i;

	i = 0;
	if (ft_strchr(map[i], 'X'))
		return (free_tab(map), 1);
	while (map[i + 1])
	{
		if (map[i][0] == 'X' || map[i][ft_strlen(map[i]) - 1] == 'X')
			return (free_tab(map), 1);
		i++;
	}
	if (ft_strchr(map[i], 'X'))
		return (free_tab(map), 1);
	return (free_tab(map), 0);
}

int	path_finding(t_win *win, char **map)
{
	int	i;
	int	j;
	int	n;

	if (path_finding_start(map) != 1)
		return (free_tab(map), free_win(win, "Something went wrong\n"), -1);
	n = 1;
	while (n)
	{
		n = 0;
		i = -1;
		while (map[++i])
		{
			j = -1;
			while (map[i][++j])
			{
				if (map[i][j] == 'X')
					n += path_finding_aux(map, j, i);
			}
		}
	}
	return (path_finding_verif(map));
}

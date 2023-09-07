/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:41:20 by djanusz           #+#    #+#             */
/*   Updated: 2023/09/07 16:59:03 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cube.h"

void	mini_map_aux(t_img *mini_map, char **map, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mini_map->height / ft_strslen(map))
	{
		j = -1;
		while (++j < mini_map->width / ft_strlen(map[i]))
		{
			if (map[x][y] == '0')
				my_mlx_pixel_put(mini_map, j + y, i + x, 0xffffff);
			else
				my_mlx_pixel_put(mini_map, j + y, i + x, 0x0fffaf);
		}
	}
}

void	mini_map(t_win *win, t_player *info, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			mini_map_aux(&win->mini_map, map, i, j);
	}
	// int	i;
	// int	j;

	// i = -1;
	// while (++i < 5)
	// {
	// 	j = -1;
	// 	while (++j < 5)
	// 	{
	// 		if (mini_map_check(map, info->pos_x + i - 2, info->pos_y + j - 2))
	// 			mini_map_aux(&win->mini_map, i * 30, j * 30, 0x0fffaf);
	// 		else
	// 			mini_map_aux(&win->mini_map, i * 30, j * 30, 0xffffff);
	// 	}
	// }
	(void)info;
	(void)map;
	past_img_to_frame(win->frame, win->mini_map, 10, 10);
}

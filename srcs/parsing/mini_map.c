/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:41:20 by djanusz           #+#    #+#             */
/*   Updated: 2023/08/16 18:12:06 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cube.h"

void	mini_map_aux(t_img *mini_map, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while(i < 30)
	{
		j = 0;
		while (j < 30)
		{
			my_mlx_pixel_put(mini_map, j + y, i + x, color);
			j++;
		}
		i++;
	}
}

int	mini_map_check(char **map, int x, int y)
{
	if (x < 0 || y < 0 || x > ft_strlen(map[x]) || y > ft_strslen(map))
		return (1);
	return (map[x][y] != '0');
}

void	mini_map(t_win *win, t_player *player, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			if (mini_map_check(map, player->pos_x + i - 2, player->pos_y + j - 2))
				mini_map_aux(&win->mini_map, i * 30, j * 30, 0x0fffaf);
			else
				mini_map_aux(&win->mini_map, i * 30, j * 30, 0xffffff);
			j++;
		}
		i++;
	}
	past_img_to_frame(win->frame, win->mini_map, 10, 10);
}

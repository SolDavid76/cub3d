/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:41:20 by djanusz           #+#    #+#             */
/*   Updated: 2023/09/11 13:57:46 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cube.h"

void	mini_map_aux(t_img *mini_map, t_coords coords, char **map, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mini_map->height / ft_strslen(map))
	{
		j = -1;
		while (++j < mini_map->width / ft_strlen(map[0]))
			my_mlx_pixel_put(mini_map, j + coords.y, i + coords.x, color);
	}
}

void	mini_map(t_win *win, t_player *player, char **map)
{
	t_coords	coords;
	int			i;
	int			j;

	i = -1;
	coords.x = 0;
	while (map[++i])
	{
		j = -1;
		coords.y = 0;
		while (map[i][++j])
		{
			if (i == (int)player->pos_x && j == (int)player->pos_y)
				mini_map_aux(win->mini_map, coords, map, 0xff0000);
			else if (map[i][j] == '0')
				mini_map_aux(win->mini_map, coords, map, 0xffffff);
			else
				mini_map_aux(win->mini_map, coords, map, 0x0fffa0);
			coords.y += win->mini_map->width / ft_strlen(map[0]);
		}
		coords.x += win->mini_map->height / ft_strslen(map);
	}
	past_img_to_frame(win->frame, *win->mini_map, 10, 10);
}

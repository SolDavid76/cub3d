/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:41:20 by djanusz           #+#    #+#             */
/*   Updated: 2023/08/16 11:13:43 by djanusz          ###   ########.fr       */
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

void	mini_map(t_win *win, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			if (win->data->map[(int)player->pos_x + (i - 2)][(int)player->pos_y + (j - 2)] == '1')
				mini_map_aux(&win->mini_map, i * 30, j * 30, 0x0fffaf);
			else
				mini_map_aux(&win->mini_map, i * 30, j * 30, 0xffffff);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(win->mlx, win->ptr, win->mini_map.ptr, 10, 10);
}

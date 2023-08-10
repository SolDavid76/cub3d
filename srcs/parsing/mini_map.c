/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:41:20 by djanusz           #+#    #+#             */
/*   Updated: 2023/08/10 11:56:08 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cube.h"

void	mini_map_aux(t_img *mini_map)
{
	int	i;
	int	j;

	i = 0;
	while(i < 30)
	{
		j = 0;
		while (j < 30)
		{
			*(int *)(mini_map->pxl + (i * mini_map->len) + (j * (mini_map->bpp / 8))) = 0x00ff00;
			// *(int *)mini_map->pxl = 0x00ff00;
			j++;
		}
		i++;
	}
}

void	mini_map(t_win *win, t_player *player)
{
	int	i;

	i = 0;
	while (i < win->mini_map.len)
	{
		if (win->data->map[(int)player->pos_x - 2][(int)player->pos_y - 2] == '1')
			mini_map_aux(&win->mini_map);
		i += 4;
	}
	mlx_put_image_to_window(win->mlx, win->ptr, win->mini_map.ptr, 10, 10);
}

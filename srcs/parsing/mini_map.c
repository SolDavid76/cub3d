/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:41:20 by djanusz           #+#    #+#             */
/*   Updated: 2023/08/08 16:31:06 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cube.h"

void	mini_map(t_win *win, t_player *player)
{
	int	i;
	(void)player;
	i = 0;
	while (i < win->minimap->len)
	{
		*(int *)(win->minimap->pxl + i) = 0xff0000;
		i += 4;
	}
	mlx_put_image_to_window(win->mlx, win->ptr, win->minimap->ptr, 10, 10);
}

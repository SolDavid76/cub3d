/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:41:20 by djanusz           #+#    #+#             */
/*   Updated: 2023/08/03 13:09:12 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cube.h"

void	mini_map(t_win *win, t_player *player)
{
	(void)player;
	mlx_put_image_to_window(win->mlx, win->ptr, win->minimap.ptr, 10, 10);
	mlx_string_put(win->mlx, win->ptr, 70, 85, 0xFFFFFF, "W.I.P");
}

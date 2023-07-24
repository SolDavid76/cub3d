/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:51:57 by djanusz           #+#    #+#             */
/*   Updated: 2023/07/24 12:55:36 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_win	init_window(void)
{
	t_win	win;
	t_img	tmp;

	win.mlx = mlx_init();
	win.width = 720;
	win.height = 480;
	tmp.ptr = mlx_new_image(win.mlx, win.width, win.height);
	tmp.pxl = mlx_get_data_addr(tmp.ptr, &tmp.bpp, &tmp.len, &tmp.endian);
	win.frame = tmp;
	return (win);
}

t_img	*ft_img(void *mlx, char *path, int width, int height)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->ptr = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!img->ptr)
		return (free(img), NULL);
	img->pxl = mlx_get_data_addr(img->ptr, &img->bpp, &img->len, &img->endian);
	return (img);
}

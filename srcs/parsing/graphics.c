/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:51:57 by djanusz           #+#    #+#             */
/*   Updated: 2023/08/28 10:10:57 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_win	*init_window(void)
{
	t_win	*win;
	t_img	tmp;

	win = malloc(sizeof(t_win));
	if (!win)
		ft_exit("NOT ENOUGH MEMORY\n");
	win->mlx = mlx_init();
	win->width = WIDTH;
	win->height = HEIGHT;
	tmp.ptr = mlx_new_image(win->mlx, win->width, win->height);
	tmp.pxl = mlx_get_data_addr(tmp.ptr, &tmp.bpp, &tmp.len, &tmp.endian);
	win->frame = tmp;
	tmp.ptr = mlx_new_image(win->mlx, 150, 150);
	tmp.pxl = mlx_get_data_addr(tmp.ptr, &tmp.bpp, &tmp.len, &tmp.endian);
	win->mini_map = tmp;
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

void	past_img_to_frame(t_img frame, t_img img, int x, int y)
{
	char	*dst;
	char	*src;
	int		i;
	int		j;
	int		p;

	i = -1;
	while (++i < 150)
	{
		j = -1;
		while (++j < 150)
		{
			src = img.pxl + (i * img.len + j * (img.bpp / 8));
			dst = frame.pxl + ((i + y) * frame.len + (j + x) * (frame.bpp / 8));
			p = -1;
			while (++p < 4)
				dst[p] = src[p];
		}
	}
}

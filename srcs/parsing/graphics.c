/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:51:57 by djanusz           #+#    #+#             */
/*   Updated: 2023/09/11 13:59:31 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
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
	tmp.width = WIDTH;
	tmp.height = HEIGHT;
	tmp.ptr = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	tmp.pxl = mlx_get_data_addr(tmp.ptr, &tmp.bpp, &tmp.len, &tmp.endian);
	win->frame = tmp;
	return (win);
}

t_img	*init_minimap(void *mlx, char **map)
{
	t_img	*res;

	res = malloc(sizeof(t_img));
	if (!res)
		ft_exit("NOT ENOUGH MEMORY");
	res->width = (int)((WIDTH * 0.2) / ft_strlen(map[0])) * ft_strlen(map[0]);
	res->height = (int)((HEIGHT * 0.2) / ft_strslen(map)) * ft_strslen(map);
	res->ptr = mlx_new_image(mlx, WIDTH * 0.2, HEIGHT * 0.2);
	res->pxl = mlx_get_data_addr(res->ptr, &res->bpp, &res->len, &res->endian);
	return (res);
}

t_img	*ft_img(void *mlx, char *path)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->ptr = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
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
	while (++i < img.height)
	{
		j = -1;
		while (++j < img.width)
		{
			src = img.pxl + (i * img.len + j * (img.bpp / 8));
			dst = frame.pxl + ((i + y) * frame.len + (j + x) * (frame.bpp / 8));
			p = -1;
			while (++p < 4)
				dst[p] = src[p];
		}
	}
}

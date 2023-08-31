/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:15:48 by ennollet          #+#    #+#             */
/*   Updated: 2023/08/28 10:39:19 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x > WIDTH - 1 || y > HEIGHT - 1)
		return ;
	pixel = img->pxl + (y * img->len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	get_color(t_img *img, int x, int y)
{
	return (*(int *)(img->pxl + (y * img->len + x * (img->bpp / 8))));
}

void	draw(t_ray *ray, int x, int y, t_img *img)
{
	int	color;

	color = get_color(img, ray->text_x, ray->text_y);
	my_mlx_pixel_put(&ray->win->frame, x, y, color);
}

void	draw_game(t_ray *ray, int x, t_win *win, t_player *player)
{
	int	y;

	y = 0;
	while (y < ray->start_h)
		my_mlx_pixel_put(&win->frame, x, y++, ray->win->data->sky);
	while (y < ray->end_h)
	{
		ray->tex_pos += ray->step;
		ray->text_y = (int)ray->tex_pos;
		if (ray->side == 1 && ray->ray_dir_y < 0)
			draw(ray, x, y, ray->win->data->west);
		else if (ray->side == 1 && ray->ray_dir_y >= 0)
			draw(ray, x, y, ray->win->data->east);
		else if (ray->side == 0 && ray->ray_dir_x < 0)
			draw(ray, x, y, ray->win->data->north);
		else if (ray->side == 0 && ray->ray_dir_x >= 0)
			draw(ray, x, y, ray->win->data->south);
		y++;
	}
	while (y < HEIGHT - 1)
		my_mlx_pixel_put(&win->frame, x, y++, ray->win->data->floor);
	(void)player;
}

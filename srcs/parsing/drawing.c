/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:15:48 by ennollet          #+#    #+#             */
/*   Updated: 2023/08/07 17:48:56 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	get_color(t_img *img, int x, int y)
{
	// printf("%d %d \n", x ,y );
	return (*(int *)(img->pxl + (y * img->len + x * (img->bpp / 8))));
}

void draw(t_ray *ray, int x, int y, t_img *img, t_win *win)
{
	int	color;

	color = get_color(img, ray->text_x, ray->text_y);
	my_mlx_pixel_put(&win->frame, x, y, color);
}

void	draw_game(t_ray *ray, int x, t_win *win, t_player *player)
{
	int	y;

	y = 0;
	while (y != ray->start_h)
			my_mlx_pixel_put(&win->frame, x, y++, ray->win->data->sky);								
	while (y < ray->end_h)
	{
		// get_text(ray, player);
		ray->tex_pos += ray->step;
		// ray->text_y = (int)ray->tex_pos & (ray->hauteur - 1);
		ray->text_y = (y * 2 - HEIGHT + ray->hauteur) * (50 / 2) / ray->hauteur;
		// if (ray->side == 1 && player->dir_y < 0)
		// 	printf("hello 111111\n");
		// printf("%d %f\n", ray->side, player->dir_y);
		if (ray->side == 1 && ray->ray_dir_y < 0)
			// my_mlx_pixel_put(&data->img, x, y, 0xf2);
			draw(ray, x, y, ray->win->data->south, win);
		else if (ray->side == 1 && ray->ray_dir_y >= 0)
			// my_mlx_pixel_put(&win->img, x, y, 0xf2);
			draw(ray, x, y, ray->win->data->north, win);
		else if (ray->side == 0 && ray->ray_dir_x < 0)
			// my_mlx_pixel_put(&win->img, x, y, 0xb1b5b2);
			draw(ray, x, y, ray->win->data->west, win);
		else if (ray->side == 0 && ray->ray_dir_x >= 0)
			draw(ray, x, y, ray->win->data->east, win);
			// my_mlx_pixel_put(&data->img, x, y, 0xb1b5b2);
		y++;
	}
	while (y < HEIGHT - 1)
		my_mlx_pixel_put(&win->frame, x, y++, ray->win->data->floor);
	(void)player;
}
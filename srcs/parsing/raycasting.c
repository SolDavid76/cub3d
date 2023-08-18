/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:09:01 by ennollet          #+#    #+#             */
/*   Updated: 2023/08/16 18:57:23 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	dda(t_ray *ray)
{
	while (ray->hit != 1)
	{
		get_wall_dist(ray);
	}
	if (ray->side == 0)
		ray->fix_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->fix_dist = (ray->side_dist_y - ray->delta_dist_y);
}

void	get_text(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->fix_dist * ray->ray_dir_y;
	else
		ray->wall_x = player->pos_x + ray->fix_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->text_x = (ray->wall_x *(TEXT_WIDTH));
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->text_x = TEXT_WIDTH - ray->text_x - 1;
	else if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->text_x = TEXT_WIDTH - ray->text_x - 1;
	ray->step = 1.0 * TEXT_WIDTH / ray->hauteur;
	ray->tex_pos = (ray->start_h - (ray->jump / ray->fix_dist) - HEIGHT / 2 \
	+ ray->hauteur / 2) * ray->step;
}
void	frame_jump(t_ray *ray)
{
	if (ray->jump_nb == 4 * 2)
		ray->jump =  2*  50;
	else if (ray->jump_nb == 4 * 4)
		ray->jump =  2*  100;
	else if (ray->jump_nb == 4 * 6)
		ray->jump =  2*  150;
	else if (ray->jump_nb == 4 * 8)
		ray->jump =  2*  200;
	else if (ray->jump_nb == 4 * 10)
		ray->jump =  2*  200;
	else if (ray->jump_nb == 4 * 12)
		ray->jump =  2*  200;
	else if (ray->jump_nb == 4 * 14)
		ray->jump =  2*  130;
	else if (ray->jump_nb == 4 * 16)
		ray->jump =  2*  65;
	else if (ray->jump_nb == 4 * 18)
		ray->jump =  2*  0;
	if (ray->jump_nb && ++ray->jump_nb == 4 * 20)
		ray->jump_nb = 0;

}
int	make_raycasting(t_ray *ray)
{
	int	x;

	x = 0;
	ray->width = WIDTH;
	frame_jump(ray);
	exec_hook(ray, ray->hook);
	while (x < ray->width)
	{
		init_ray(ray, WIDTH, x, ray->player);
		dda(ray);
		ray->hauteur = (int)(HEIGHT / ray->fix_dist);
		ray->start_h = (-ray->hauteur) / 2 + HEIGHT / 2 \
		+ (ray->jump / ray->fix_dist);
		ray->end_h = ray->hauteur / 2 + HEIGHT / 2 \
		+ (ray->jump / ray->fix_dist);
		if (ray->start_h < 0)
			ray->start_h = 0;
		if (ray->end_h >= HEIGHT)
			ray->end_h = HEIGHT - 1;
		get_text(ray, ray->player);
		draw_game(ray, x, ray->win, ray->player);
		x++;
	}
	mlx_put_image_to_window(ray->win->mlx, ray->win->ptr, ray->win->frame.ptr, 0, 0);
	// mini_map(ray->win, ray->player);
	return (0);
}

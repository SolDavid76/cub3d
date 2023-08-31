/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:09:01 by ennollet          #+#    #+#             */
/*   Updated: 2023/08/31 10:31:54 by ennollet         ###   ########.fr       */
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

void	mouse_ation(t_ray *ray)
{
	int	m_x;
	int	m_y;

	if (ray->pause == 0)
	{
		// mlx_mouse_hide(ray->win->mlx, ray->win->ptr);
		mlx_mouse_get_pos(ray->win->mlx, ray->win->ptr, &m_x, &m_y);
		if (m_x > WIDTH / 2)
			ft_rotate(ray->player, (double)(-M_SPEED * \
			((m_x - (WIDTH / 2)) * 100 / WIDTH)));
		else if (m_x < WIDTH / 2)
			ft_rotate(ray->player, (double)(-M_SPEED * \
			((m_x - (WIDTH / 2)) * 100 / WIDTH)));
		mlx_mouse_move(ray->win->mlx, ray->win->ptr, WIDTH / 2, HEIGHT / 2);
	}	
}

void	define_height(t_ray *ray)
{
	ray->hauteur = (int)(HEIGHT / ray->fix_dist);
	if (ray->hauteur < 0)
		ray->hauteur = INT_MAX;
	ray->start_h = (-ray->hauteur) / 2 + HEIGHT / 2 \
	+ (ray->jump / ray->fix_dist);
	ray->end_h = ray->hauteur / 2 + HEIGHT / 2 \
	+ (ray->jump / ray->fix_dist);
	if (ray->start_h < 0)
		ray->start_h = 0;
	if (ray->end_h >= HEIGHT)
		ray->end_h = HEIGHT - 1;
}

int	make_raycasting(t_ray *ray)
{
	int	x;

	x = 0;
	frame_jump(ray);
	exec_hook(ray, ray->hook);
	while (x < WIDTH)
	{
		init_ray(ray, WIDTH, x, ray->player);
		dda(ray);
		define_height(ray);
		get_text(ray, ray->player);
		draw_game(ray, x, ray->win, ray->player);
		x++;
	}
	mouse_ation(ray);
	mini_map(ray->win, ray->player, ray->win->data->map);
	mlx_put_image_to_window(ray->win->mlx, ray->win->ptr, ray->win->frame.ptr, 0, 0);
	return (0);
}

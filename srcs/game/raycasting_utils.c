/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:53:52 by ennollet          #+#    #+#             */
/*   Updated: 2023/09/11 15:46:51 by ennollet         ###   ########.fr       */
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

void	get_delta(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = INT_MAX;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = INT_MAX;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	get_step_side(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1 - player->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1 - player->pos_y) * ray->delta_dist_y;
	}
}

void	init_ray(t_ray *ray, int width, int x, t_player *player)
{
	ray->camera_x = 2 * x / (double)width - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	get_delta(ray);
	ray->hit = 0;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->hauteur = 0;
	get_step_side(ray, player);
}

void	get_wall_dist(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
	if (ray->win->data->map[ray->map_x][ray->map_y] == '1')
		ray->hit = 1;
}

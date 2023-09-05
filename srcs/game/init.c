/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:56:49 by ennollet          #+#    #+#             */
/*   Updated: 2023/09/05 10:59:53 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_hook	*init_hook(t_hook *hook)
{
	hook = malloc(sizeof(t_hook));
	hook->hook_echap = 0;
	hook->hook_w = 0;
	hook->hook_a = 0;
	hook->hook_s = 0;
	hook->hook_d = 0;
	hook->hook_rotate_l = 0;
	hook->hook_rotate_r = 0;
	hook->hook_jump = 0;
	hook->hook_crouch = 0;
	hook->hook_sprint = 0;
	hook->hook_tab = 0;
	return (hook);
}

void	init_dir(t_player *player, t_ray *ray)
{
	if (ray->win->data->spawn_dirr == 'N')
	{
		player->dir_x = -1;
		player->plane_y = 0.66;
	}
	else if (ray->win->data->spawn_dirr == 'S')
	{
		player->dir_x = 1;
		player->plane_y = -0.66;
	}	
	else if (ray->win->data->spawn_dirr == 'E')
	{
		player->dir_y = 1;
		player->plane_x = 0.66;
	}
	else if (ray->win->data->spawn_dirr == 'W')
	{
		player->dir_y = -1;
		player->plane_x = -0.66;
	}
}

t_player	*init_player(t_player *player, t_ray *ray)
{
	player->pos_x = ray->win->data->spawn_x + 0.5;
	player->pos_y = ray->win->data->spawn_y + 0.5;
	init_dir(player, ray);
	player->rot_speed = R_SPEED;
	return (player);
}

void	init_struct(t_ray *ray)
{
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->delta_dist_x = 0;
	ray->delta_dist_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->side = 0;
	ray->fix_dist = 0;
	ray->hauteur = 0;
	ray->start_h = 0;
	ray->end_h = 0;
	ray->jump = 0;
	ray->jump_nb = 0;
	ray->width = 0;
	ray->wall_x = 0;
	ray->text_x = 0;
	ray->text_y = 0;
	ray->step = 0;
	ray->tex_pos = 0;
	ray->speed = 1;
	ray->pause = 0;
}

t_player	*init_struct_player(t_player *player)
{
	player = malloc(sizeof(t_player));
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->rot_speed = 0;
	return (player);
}

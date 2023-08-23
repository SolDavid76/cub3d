/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:36:55 by ennollet          #+#    #+#             */
/*   Updated: 2023/08/23 10:30:24 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "parsing.h"

double	ft_abs(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

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
	player->rot_speed = 0.01;
	return (player);
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

void init_struct(t_ray *ray)
{
	ray->ray_dir_x = 1;
	ray->ray_dir_y = 1;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->delta_dist_x = 0;
	ray->delta_dist_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = 0;
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
}

t_player *init_struct_player(t_player *player)
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
int	main(int ac, char **av)
{
	t_ray		*ray;
	
	ray = malloc(sizeof(t_ray));
	init_struct(ray);
	ray->player = init_struct_player(ray->player);
	ray->win = parsing(av[1]);
	ray->win->ptr = mlx_new_window(ray->win->mlx, ray->win->width, \
	ray->win->height, "cub3D");
	ray->player = init_player(ray->player, ray);
	ray->hook = init_hook(ray->hook);
	ray->jump_nb = 0;
	make_raycasting(ray);
	mlx_loop_hook(ray->win->mlx, make_raycasting, ray);
	mlx_hook(ray->win->ptr, KeyPress, KeyPressMask, ft_keypress, ray->hook);
	mlx_hook(ray->win->ptr, KeyRelease, KeyReleaseMask, ft_key_release, ray->hook);
	mlx_hook(ray->win->ptr, 17, 0, &ft_mlx_exit, ray->win);
	mlx_loop(ray->win->mlx);
	mlx_destroy_image(ray->win->mlx, ray->win->frame.ptr);
	mlx_destroy_display(ray->win->mlx);
	free(ray->win->mlx);
	(void)ac;
}

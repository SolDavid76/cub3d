/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:36:55 by ennollet          #+#    #+#             */
/*   Updated: 2023/08/14 11:50:47 by ennollet         ###   ########.fr       */
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
	player = malloc(sizeof(t_player));
	player->pos_x = ray->win->data->spawn_x + 0.5;
	player->pos_y = ray->win->data->spawn_y + 0.5;
	init_dir(player, ray);
	player->rot_speed = 0.1;
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

int	main(int ac, char **av)
{
	t_ray		ray;

	ray.win = parsing(av[1]);
	ray.win->ptr = mlx_new_window(ray.win->mlx, ray.win->width, \
	ray.win->height, "cub3D");
	ray.player = init_player(ray.player, &ray);
	ray.jump_nb = 0;
	make_raycasting(&ray);
	mlx_loop_hook(ray.win->mlx, make_raycasting, &ray);
	mlx_hook(ray.win->ptr, KeyPress, KeyPressMask, ft_keypress, &ray);
	mlx_hook(ray.win->ptr, 17, 0, &ft_mlx_exit, ray.win);
	mlx_loop(ray.win->mlx);
	mlx_destroy_image(ray.win->mlx, ray.win->frame.ptr);
	mlx_destroy_display(ray.win->mlx);
	free(ray.win->mlx);
	(void)ac;
}

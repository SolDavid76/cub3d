/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:36:55 by ennollet          #+#    #+#             */
/*   Updated: 2023/08/11 15:05:41 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "parsing.h"

// t_ray	ray;
// char **bob;

double	ft_abs(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	if (x < 0 || y < 0 || x > WIDTH - 1 || y > HEIGHT - 1)
		return ;
	pixel = img->pxl + (y * img->len + x * (img->bpp / 8));
	*(int *)pixel = color;
}
void	init_dir(t_player *player, t_ray *ray)
{
	if (ray->win->data->spawn_dirr == 'N')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (ray->win->data->spawn_dirr == 'S')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}	
	else if (ray->win->data->spawn_dirr == 'E')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (ray->win->data->spawn_dirr == 'W')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
}
t_player	*init_player(t_player *player, t_ray *ray)
{
	player = malloc(sizeof(t_player));
	player->pos_x = ray->win->data->spawn_x + 0.1;
	player->pos_y = ray->win->data->spawn_y + 0.1;
	// player->dir_x = -1;
	// player->dir_y = 0;
	// player->plane_x = 0;
	// player->plane_y = 0.66;
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

int main(int ac, char **av)
{
	// t_data		data;
	t_ray		ray;
	// t_player	player;
	// t_win		win;
	// t_game		game;
	
	ray.win = parsing(av[1]);
	// ray.win = &win;
	ray.win->ptr = mlx_new_window(ray.win->mlx, ray.win->width, ray.win->height, "cub3D");
	// ray.win = &win;
	ray.player = init_player(ray.player, &ray);
	
	while (1)
	{
		make_raycasting(&ray, ray.win, ray.player);
		mlx_hook(ray.win->ptr, KeyPress, KeyPressMask, &ft_keypress, &ray);
		mlx_hook(ray.win->ptr, 17, 0, &ft_mlx_exit, &ray.win);
		mlx_loop(ray.win->mlx);
	}
	mlx_destroy_image(ray.win->mlx, ray.win->frame.ptr);
	mlx_destroy_display(ray.win->mlx);
	free(ray.win->mlx);
	(void)ac;
	// (void)ray.win;
}
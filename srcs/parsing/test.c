/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:36:55 by ennollet          #+#    #+#             */
/*   Updated: 2023/08/07 17:35:52 by ennollet         ###   ########.fr       */
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
	// if (x < 0 || y < 0 || x > WIDTH - 1 || y > HEIGHT - 1)
	// 	return ;
	pixel = img->pxl + (y * img->len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	ft_mlx_exit(t_win *win)
{
	mlx_destroy_image(win->mlx, win->frame.ptr);
	mlx_destroy_window(win->mlx, win->ptr);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	exit(0);
}

void	ft_rotate(t_player *player, double rot_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y * sin(rot_speed);
	player->dir_y = old_dir_x * sin(rot_speed) + player->dir_y * cos(rot_speed);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y * sin(rot_speed);
	player->plane_y = old_plane_x * sin(rot_speed) + player->plane_y * cos(rot_speed);
}

void	w_and_s(t_ray *ray, t_player *player, int sign)
{
	if (sign == 0)
	{
		if (ray->win->data->map[(int)(player->pos_x + player->dir_x *(0.2))][(int)player->pos_y] != '1')
			player->pos_x += player->dir_x *(0.2);
		if (ray->win->data->map[(int)player->pos_x][(int)(player->pos_y + player->dir_y *(0.2))] != '1')
			player->pos_y += player->dir_y *(0.2);
	}
	else
	{
		if (ray->win->data->map[(int)(player->pos_x - player->dir_x *(0.2))][(int)player->pos_y] != '1')
			player->pos_x -= player->dir_x *(0.2);
		if (ray->win->data->map[(int)player->pos_x][(int)(player->pos_y - player->dir_y *(0.2))] != '1')
			player->pos_y -= player->dir_y *(0.2);
	}

}

void	a_and_d(t_ray *ray, t_player *player, int sign)
{
	if (sign == 0)
	{
		if (ray->win->data->map[(int)(player->pos_x + player->plane_x *(0.12))][(int)player->pos_y] != '1')
			player->pos_x += player->plane_x *(0.12);
		if (ray->win->data->map[(int)player->pos_x][(int)(player->pos_y + player->plane_y *(0.12))] != '1')
			player->pos_y += player->plane_y *(0.12);
	}
	else
	{
		if (ray->win->data->map[(int)(player->pos_x - player->plane_x *(0.12))][(int)player->pos_y] != '1')
			player->pos_x -= player->plane_x *(0.12);
		if (ray->win->data->map[(int)player->pos_x][(int)(player->pos_y - player->plane_y *(0.12))] != '1')
			player->pos_y -= player->plane_y *(0.12);
	}
}


int	ft_keypress(int keycode, t_ray *ray)
{		
	printf ("keycode : %d\n", keycode);
	if (keycode == 65307)
		ft_mlx_exit(ray->win);
	if (keycode == 119 || keycode == 122) // W
		w_and_s(ray, ray->player, 0);
	if (keycode == 97 || keycode == 113) // A
	a_and_d(ray, ray->player, 1);
	if (keycode == 115) // S
		w_and_s(ray, ray->player, 1);
	if (keycode == 100) // D
	a_and_d(ray, ray->player, 0);
	if (keycode  == 65363) // droite
		ft_rotate(ray->player, -ray->player->rot_speed);
	if (keycode == 65361)
		ft_rotate(ray->player, ray->player->rot_speed);
	make_raycasting(ray, ray->win, ray->player);
	return (0);
}

t_player	*init_player(t_player *player)
{
	player = malloc(sizeof(t_player));
	player->pos_x = 5.5;
	player->pos_y = 1.5;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
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
	t_win		win;
	// t_game		game;

	win = parsing(av[1]);
	win.ptr = mlx_new_window(win.mlx, win.width, win.height, "cub3D");
	ray.win = &win;
	ray.player = init_player(ray.player);
	
	while (1)
	{
		make_raycasting(&ray, &win, ray.player);
		mlx_hook(win.ptr, KeyPress, KeyPressMask, &ft_keypress, &ray);
		mlx_hook(win.ptr, 17, 0, &ft_mlx_exit, &win);
		mlx_loop(win.mlx);
	}
	mlx_destroy_image(win.mlx, win.frame.ptr);
	mlx_destroy_display(win.mlx);
	free(win.mlx);
	(void)ac;
}
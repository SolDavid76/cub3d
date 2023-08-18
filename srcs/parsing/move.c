/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:47:42 by ennollet          #+#    #+#             */
/*   Updated: 2023/08/16 16:54:53 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_mlx_exit(t_win *win)
{
	mlx_destroy_image(win->mlx, win->frame.ptr);
	mlx_destroy_window(win->mlx, win->ptr);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	exit(0);
}

void	ft_rotate(t_player *pl, double rt_spd)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = pl->dir_x;
	pl->dir_x = pl->dir_x * cos(rt_spd) - pl->dir_y * sin(rt_spd);
	pl->dir_y = old_dir_x * sin(rt_spd) + pl->dir_y * cos(rt_spd);
	old_plane_x = pl->plane_x;
	pl->plane_x = pl->plane_x * cos(rt_spd) - pl->plane_y * sin(rt_spd);
	pl->plane_y = old_plane_x * sin(rt_spd) + pl->plane_y * cos(rt_spd);
}

void	w_and_s(t_ray *ray, t_player *player, int sign)
{
	if (sign == 0)
	{
		if (ray->win->data->map[(int)(player->pos_x + player->dir_x *(0.2))] \
		[(int)player->pos_y] != '1')
			player->pos_x += player->dir_x *(0.2);
		if (ray->win->data->map[(int)player->pos_x] \
		[(int)(player->pos_y + player->dir_y *(0.2))] != '1')
			player->pos_y += player->dir_y *(0.2);
	}
	else
	{
		if (ray->win->data->map[(int)(player->pos_x - player->dir_x *(0.2))] \
		[(int)player->pos_y] != '1')
			player->pos_x -= player->dir_x *(0.2);
		if (ray->win->data->map[(int)player->pos_x] \
		[(int)(player->pos_y - player->dir_y *(0.2))] != '1')
			player->pos_y -= player->dir_y *(0.2);
	}
}

void	a_and_d(t_ray *ray, t_player *player, int sign)
{
	if (sign == 0)
	{
		if (ray->win->data->map[(int)(player->pos_x + player->plane_x *(0.12))] \
		[(int)player->pos_y] != '1')
			player->pos_x += player->plane_x *(0.12);
		if (ray->win->data->map[(int)player->pos_x] \
		[(int)(player->pos_y + player->plane_y *(0.12))] != '1')
			player->pos_y += player->plane_y *(0.12);
	}
	else
	{
		if (ray->win->data->map[(int)(player->pos_x - player->plane_x *(0.12))] \
		[(int)player->pos_y] != '1')
			player->pos_x -= player->plane_x *(0.12);
		if (ray->win->data->map[(int)player->pos_x] \
		[(int)(player->pos_y - player->plane_y *(0.12))] != '1')
			player->pos_y -= player->plane_y *(0.12);
	}
}

void	jump(t_ray *ray)
{
	printf("%d\n", ray->jump_nb);
	if (ray->jump_nb == 0)
		ray->jump_nb = 1;
}

void	crouch(t_ray *ray)
{
	if (ray->jump != -75)
		ray->jump = -75;
	else
		ray->jump = 0;
}

int	ft_keypress(int keycode, t_ray *ray)
{
	// printf ("keycode : %d\n", keycode);
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
	if (keycode == 65363) // droite
		ft_rotate(ray->player, -ray->player->rot_speed);
	if (keycode == 65361)
		ft_rotate(ray->player, ray->player->rot_speed);
	if (keycode == 32)
		jump(ray);
	if (keycode == 65505)
		crouch(ray);
	// make_raycasting(ray);
	return (0);
}

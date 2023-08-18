/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:47:42 by ennollet          #+#    #+#             */
/*   Updated: 2023/08/18 14:43:28 by ennollet         ###   ########.fr       */
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
	// printf("1 %f\n", player->pos_x);
	if (sign == 0)
	{
		if (ray->win->data->map[(int)(player->pos_x + player->dir_x *(0.02))] \
		[(int)player->pos_y] != '1')
			player->pos_x += player->dir_x *(0.02);
		if (ray->win->data->map[(int)player->pos_x] \
		[(int)(player->pos_y + player->dir_y *(0.02))] != '1')
			player->pos_y += player->dir_y *(0.02);
	}
	else
	{
		if (ray->win->data->map[(int)(player->pos_x - player->dir_x *(0.02))] \
		[(int)player->pos_y] != '1')
			player->pos_x -= player->dir_x *(0.02);
		if (ray->win->data->map[(int)player->pos_x] \
		[(int)(player->pos_y - player->dir_y *(0.02))] != '1')
			player->pos_y -= player->dir_y *(0.02);
	}
	// printf("2 %f\n", player->pos_x);

}

void	a_and_d(t_ray *ray, t_player *player, int sign)
{
	if (sign == 0)
	{
		if (ray->win->data->map[(int)(player->pos_x + player->plane_x *(0.02))] \
		[(int)player->pos_y] != '1')
			player->pos_x += player->plane_x *(0.02);
		if (ray->win->data->map[(int)player->pos_x] \
		[(int)(player->pos_y + player->plane_y *(0.02))] != '1')
			player->pos_y += player->plane_y *(0.02);
	}
	else
	{
		if (ray->win->data->map[(int)(player->pos_x - player->plane_x *(0.02))] \
		[(int)player->pos_y] != '1')
			player->pos_x -= player->plane_x *(0.02);
		if (ray->win->data->map[(int)player->pos_x] \
		[(int)(player->pos_y - player->plane_y *(0.02))] != '1')
			player->pos_y -= player->plane_y *(0.02);
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
	if (ray->jump > -50)
		ray->jump -= 50;
}

// int	ft_keypress(int keycode, t_ray *ray)
// {
// 	printf ("keycode : %d\n", keycode);
// 	if (keycode == 65307)
// 		ft_mlx_exit(ray->win);
// 	if (keycode == 119 || keycode == 122) // W
// 		w_and_s(ray, ray->player, 0);
// 	if (keycode == 97 || keycode == 113) // A
// 		a_and_d(ray, ray->player, 1);
// 	if (keycode == 115) // S
// 		w_and_s(ray, ray->player, 1);
// 	if (keycode == 100) // D
// 		a_and_d(ray, ray->player, 0);
// 	if (keycode == 65363) // droite
// 		ft_rotate(ray->player, -ray->player->rot_speed);
// 	if (keycode == 65361)
// 		ft_rotate(ray->player, ray->player->rot_speed);
// 	if (keycode == 32)
// 		jump(ray);
// 	if (keycode == 65505)
// 		crouch(ray);
// 	// make_raycasting(ray);
// 	return (0);
// }

void	exec_hook(t_ray *ray, t_hook *hook)
{
	if (hook->hook_echap == 1)
		ft_mlx_exit(ray->win);
	if (hook->hook_w == 1)
		w_and_s(ray, ray->player, 0);
	if (hook->hook_a == 1)
		a_and_d(ray, ray->player, 1);
	if (hook->hook_s == 1)
		w_and_s(ray, ray->player, 1);
	if (hook->hook_d == 1)
		a_and_d(ray, ray->player, 0);
	if (hook->hook_rotate_r == 1)
		ft_rotate(ray->player, -ray->player->rot_speed);
	if (hook->hook_rotate_l == 1)
		ft_rotate(ray->player, ray->player->rot_speed);
	if (hook->hook_jump == 1)
		jump(ray);
	if (hook->hook_crouch == 1)
		crouch(ray);
}


int	ft_keypress(int keycode, t_hook *hook)
{
	if (keycode == 65307)
		hook->hook_echap = 1;
	if (keycode == 119)
		hook->hook_w = 1;
	if (keycode == 97)
		hook->hook_a = 1;
	if (keycode == 115) // S
		hook->hook_s = 1;
	if (keycode == 100) // D
		hook->hook_d = 1;
	if (keycode == 65363) // droite
		hook->hook_rotate_r = 1;
	if (keycode == 65361)
		hook->hook_rotate_l = 1;
	if (keycode == 32)
		hook->hook_jump = 1;
	if (keycode == 65505)
		hook->hook_crouch = 1;
	return (0);	
}

int	ft_key_release(int keycode, t_hook *hook)
{
	if (keycode == 119)
		hook->hook_w = 0;
	if (keycode == 97)
		hook->hook_a = 0;
	if (keycode == 115) // S
		hook->hook_s = 0;
	if (keycode == 100) // D
		hook->hook_d = 0;
	if (keycode == 65363) // droite
		hook->hook_rotate_r = 0;
	if (keycode == 65361)
		hook->hook_rotate_l = 0;
	if (keycode == 32)
		hook->hook_jump = 0;
	if (keycode == 65505)
		hook->hook_crouch = 0;
	return (0);	
}

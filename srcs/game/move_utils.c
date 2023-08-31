/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:20:29 by ennollet          #+#    #+#             */
/*   Updated: 2023/08/29 11:26:18 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_mlx_exit(t_ray *ray)
{
	free(ray->player);
	free(ray->hook);
	mlx_destroy_image(ray->win->mlx, ray->win->frame.ptr);
	mlx_destroy_window(ray->win->mlx, ray->win->ptr);
	mlx_destroy_display(ray->win->mlx);
	free(ray->win->mlx);
	free(ray);
	exit(0);
}

int	hitbox_player_x(t_ray *ray, t_player *p, double x, double y)
{
	int	flag;

	flag = 0;
	if (p->pos_x < x && ray->win->data->map[(int)(x + 0.1)][(int)y] == '1')
		flag = 1;
	else if (p->pos_x > x && ray->win->data->map[(int)(x - 0.1)][(int)y] == '1')
		flag = 1;
	return (flag);
}

int	hitbox_player_y(t_ray *ray, t_player *p, double x, double y)
{
	int	flag;

	flag = 0;
	if (p->pos_y < y && ray->win->data->map[(int)(x)][(int)(y + 0.1)] == '1')
		flag = 1;
	else if (p->pos_y > y && ray->win->data->map[(int)x][(int)(y - 0.1)] == '1')
		flag = 1;
	return (flag);
}

void	select_speed(t_ray *ray)
{
	if (ray->hook->hook_sprint == 1)
		ray->speed = 2;
	else if (ray->hook->hook_crouch == 1)
		ray->speed = 0.5;
	else
		ray->speed = 1;
}

void	frame_jump(t_ray *ray)
{
	if (ray->jump_nb == 3 * 2)
		ray->jump = 2 * 35;
	else if (ray->jump_nb == 3 * 4)
		ray->jump = 2 * 70;
	else if (ray->jump_nb == 3 * 6)
		ray->jump = 2 * 110;
	else if (ray->jump_nb == 3 * 8)
		ray->jump = 2 * 150;
	else if (ray->jump_nb == 3 * 10)
		ray->jump = 2 * 150;
	else if (ray->jump_nb == 3 * 12)
		ray->jump = 2 * 110;
	else if (ray->jump_nb == 3 * 13)
		ray->jump = 2 * 55;
	else if (ray->jump_nb == 3 * 16)
		ray->jump = 2 * 0;
	if (ray->jump_nb && ++ray->jump_nb == 3 * 18)
	{	
		ray->jump_nb = 0;
		ray->hook->hook_jump = 0;
	}
}

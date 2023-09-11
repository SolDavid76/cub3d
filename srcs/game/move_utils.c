/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:20:29 by ennollet          #+#    #+#             */
/*   Updated: 2023/09/11 14:27:08 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_mlx_exit(t_ray *ray)
{
	free(ray->player);
	free(ray->hook);
	free_tab(ray->win->data->map);
	free_img(ray->win->mini_map, ray->win->mlx);
	free_img(ray->win->data->north, ray->win->mlx);
	free_img(ray->win->data->south, ray->win->mlx);
	free_img(ray->win->data->west, ray->win->mlx);
	free_img(ray->win->data->east, ray->win->mlx);
	free(ray->win->data);
	mlx_destroy_image(ray->win->mlx, ray->win->frame.ptr);
	mlx_destroy_window(ray->win->mlx, ray->win->ptr);
	mlx_destroy_display(ray->win->mlx);
	free(ray->win->mlx);
	free(ray->win);
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
	if (ray->jump_nb == 2 * 2)
		ray->jump = 2 * 35;
	else if (ray->jump_nb == 2 * 4)
		ray->jump = 2 * 70;
	else if (ray->jump_nb == 2 * 6)
		ray->jump = 2 * 110;
	else if (ray->jump_nb == 2 * 8)
		ray->jump = 2 * 150;
	else if (ray->jump_nb == 2 * 10)
		ray->jump = 2 * 150;
	else if (ray->jump_nb == 2 * 12)
		ray->jump = 2 * 110;
	else if (ray->jump_nb == 2 * 13)
		ray->jump = 2 * 55;
	else if (ray->jump_nb == 2 * 16)
		ray->jump = 2 * 0;
	if (ray->jump_nb && ++ray->jump_nb == 2 * 18)
	{	
		ray->jump_nb = 0;
		ray->hook->hook_jump = 0;
	}
}

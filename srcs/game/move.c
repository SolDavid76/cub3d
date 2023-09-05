/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:47:42 by ennollet          #+#    #+#             */
/*   Updated: 2023/09/04 15:19:40 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
	double	tmp_x;
	double	tmp_y;

	if (sign == 0)
	{
		tmp_x = player->pos_x + player->dir_x * (P_SPEED * ray->speed);
		tmp_y = player->pos_y + player->dir_y * (P_SPEED * ray->speed);
		if (hitbox_player_x(ray, player, tmp_x, player->pos_y) == 0)
			player->pos_x = tmp_x;
		if (hitbox_player_y(ray, player, player->pos_x, tmp_y) == 0)
			player->pos_y = tmp_y;
	}
	else
	{
		tmp_x = player->pos_x - player->dir_x * (P_SPEED * ray->speed);
		tmp_y = player->pos_y - player->dir_y * (P_SPEED * ray->speed);
		if (hitbox_player_x(ray, player, tmp_x, player->pos_y) == 0)
		player->pos_x = tmp_x;
		if (hitbox_player_y(ray, player, player->pos_x, tmp_y) == 0)
			player->pos_y = tmp_y;
	}
}

void	a_and_d(t_ray *ray, t_player *player, int sign)
{
	double	tmp_x;
	double	tmp_y;

	if (sign == 0)
	{
		tmp_x = player->pos_x + player->plane_x * (P_SPEED * ray->speed);
		tmp_y = player->pos_y + player->plane_y * (P_SPEED * ray->speed);
		if (hitbox_player_x(ray, player, tmp_x, player->pos_y) == 0)
			player->pos_x = tmp_x;
		if (hitbox_player_y(ray, player, player->pos_x, tmp_y) == 0)
			player->pos_y = tmp_y;
	}
	else
	{
		tmp_x = player->pos_x - player->plane_x * (P_SPEED * ray->speed);
		tmp_y = player->pos_y - player->plane_y * (P_SPEED * ray->speed);
		if (hitbox_player_x(ray, player, tmp_x, player->pos_y) == 0)
			player->pos_x = tmp_x;
		if (hitbox_player_y(ray, player, player->pos_x, tmp_y) == 0)
			player->pos_y = tmp_y;
	}
}

void	jump(t_ray *ray)
{
	if (ray->jump_nb == 0)
		ray->jump_nb = 1;
}

void	crouch(t_ray *ray)
{
	if (ray->jump > -50)
		ray->jump -= 50;
}

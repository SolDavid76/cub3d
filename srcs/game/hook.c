/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:13:05 by ennollet          #+#    #+#             */
/*   Updated: 2023/08/29 11:44:18 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_pause(t_ray *ray)
{
	if (ray->hook->hook_tab == 1)
		ray->pause = 1;
	else
		ray->pause = 0;
}

void	exec_hook(t_ray *ray, t_hook *hook)
{
	if (hook->hook_echap == 1)
		ft_mlx_exit(ray);
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
	if (hook->hook_crouch == 1 && hook->hook_jump != 1)
		crouch(ray);
	if (hook->hook_crouch == 0 && hook->hook_jump == 0)
		ray->jump = 0;
	ft_pause(ray);
	select_speed(ray);
}

int	ft_keypress(int keycode, t_hook *hook)
{
	if (keycode == KEY_ESC)
		hook->hook_echap = 1;
	if (keycode == KEY_W)
		hook->hook_w = 1;
	if (keycode == KEY_A)
		hook->hook_a = 1;
	if (keycode == KEY_S)
		hook->hook_s = 1;
	if (keycode == KEY_D)
		hook->hook_d = 1;
	if (keycode == KEY_RIGHT)
		hook->hook_rotate_r = 1;
	if (keycode == KEY_LEFT)
		hook->hook_rotate_l = 1;
	if (keycode == KEY_SPACE)
		hook->hook_jump = 1;
	if (keycode == KEY_SHIFT && hook->hook_jump != 1)
		hook->hook_crouch = 1;
	if (keycode == KEY_CTRL)
		hook->hook_sprint = 1;
	if (keycode == KEY_TAB)
		hook->hook_tab = 1;
	return (0);
}

int	ft_key_release(int keycode, t_hook *hook)
{
	if (keycode == KEY_W)
		hook->hook_w = 0;
	if (keycode == KEY_A)
		hook->hook_a = 0;
	if (keycode == KEY_S)
		hook->hook_s = 0;
	if (keycode == KEY_D)
		hook->hook_d = 0;
	if (keycode == KEY_RIGHT)
		hook->hook_rotate_r = 0;
	if (keycode == KEY_LEFT)
		hook->hook_rotate_l = 0;
	if (keycode == KEY_SHIFT)
		hook->hook_crouch = 0;
	if (keycode == KEY_CTRL)
		hook->hook_sprint = 0;
	if (keycode == KEY_TAB)
		hook->hook_tab = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:36:55 by ennollet          #+#    #+#             */
/*   Updated: 2023/09/04 14:46:14 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "parsing.h"

t_ray	*init_game(t_ray *ray)
{
	init_struct(ray);
	ray->player = init_struct_player(ray->player);
	ray->player = init_player(ray->player, ray);
	ray->hook = init_hook(ray->hook);
	ray->jump_nb = 0;
	mlx_mouse_move(ray->win->mlx, ray->win->ptr, WIDTH / 2, HEIGHT / 2);
	make_raycasting(ray);
	return (ray);
}

int	main(int ac, char **av)
{
	t_ray		*ray;

	ray = malloc(sizeof(t_ray));
	ray->win = parsing(av[1]);
	ray->win->ptr = mlx_new_window(ray->win->mlx, ray->win->width, \
	ray->win->height, "cub3D");
	ray = init_game(ray);
	mlx_loop_hook(ray->win->mlx, make_raycasting, ray);
	mlx_hook(ray->win->ptr, KeyPress, KeyPressMask, ft_keypress, ray->hook);
	mlx_hook(ray->win->ptr, KeyRelease, KeyReleaseMask, ft_key_release, ray->hook);
	mlx_hook(ray->win->ptr, 17, 0, ft_mlx_exit, ray);
	mlx_loop(ray->win->mlx);
	mlx_destroy_image(ray->win->mlx, ray->win->frame.ptr);
	mlx_destroy_display(ray->win->mlx);
	free(ray->win->mlx);
	(void)ac;
}

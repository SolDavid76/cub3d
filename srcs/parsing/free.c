/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:05:53 by djanusz           #+#    #+#             */
/*   Updated: 2023/09/11 16:34:38 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_exit(char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	exit(0);
}

void	free_tab(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

void	free_img(t_img *img, void *mlx)
{
	if (img)
		mlx_destroy_image(mlx, img->ptr);
	free(img);
}

void	free_win(t_win *win, char *msg)
{
	mlx_destroy_image(win->mlx, win->frame.ptr);
	free_tab(win->data->map);
	free_img(win->mini_map, win->mlx);
	free_img(win->data->north, win->mlx);
	free_img(win->data->south, win->mlx);
	free_img(win->data->west, win->mlx);
	free_img(win->data->east, win->mlx);
	free(win->data);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	free(win);
	ft_exit(msg);
}

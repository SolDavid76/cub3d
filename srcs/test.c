/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ennollet <ennollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:36:55 by ennollet          #+#    #+#             */
/*   Updated: 2023/07/28 10:55:36 by ennollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_ray	ray;
t_data		data;

int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (0);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cube3D");
	if (data->win == NULL)
	{
		free(data->win);
		return (0);
	}
	data->img.mlx_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	return (0);
}

double	ft_abs(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

t_img	ft_image_from_xpm(t_data win, char *path, int width, int height)
{
	t_img	img;

	img.mlx_img = mlx_xpm_file_to_image(win.mlx, path, &width, &height);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);
	return (img);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	// if (x < 0 || y < 0 || x > WIDTH - 1 || y > HEIGHT - 1)
	// 	return ;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	ft_exit(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.mlx_img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
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
int	ft_keypress(int keycode, t_player *player)
{		
	printf ("keycode : %d\n", keycode);
	// printf("hello\n");
	if (keycode == 65307)
		ft_exit(&data);
	if (keycode == 119) // W
		player->pos_x -= 0.1 * (-player->dir_x);
	if (keycode == 97) // A
		player->pos_y -= 0.1;
	if (keycode == 115) // S
		player->pos_x += 0.1 * (-player->dir_x);
	if (keycode == 100) // D
		player->pos_y += 0.1;
	// printf("pos_y %f\n", player->pos_y);
	if (keycode  == 65363) // droite
		ft_rotate(player, -player->rot_speed);
	if (keycode == 65361)
		ft_rotate(player, player->rot_speed);
	make_raycasting(&ray, &data, player);
	return (0);
}

	int bob[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1,0,1,0,1,1,1,1,1,1,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int boby[6][6]=
{
	{1,1,1,1,1,1},
	{1,0,0,0,1,1},
	{1,0,0,0,0,1},
	{1,0,0,1,0,1},
	{1,1,1,1,0,1},
	{1,1,1,1,1,1}
};
int	init_player(t_player *player)
{
	player->pos_x = 17;
	player->pos_y = 17;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
	player->rot_speed = 0.1;
	return (0);
}
void	get_delta(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = INT_MAX;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = INT_MAX;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	get_step_side(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1 - player->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;				
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1 - player->pos_y) * ray->delta_dist_y;
	}
}
void	init_ray(t_ray *ray, int width, int x, t_player *player)
{
	ray->camera_x = 2 * x / (double)width - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	get_delta(ray);
	ray->hit = 0;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->hauteur = 0;
	get_step_side(ray, player);

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
	if (bob[ray->map_x][ray->map_y] == 1)
		ray->hit = 1;
}

void	dda(t_ray *ray)
{
	while (ray->hit != 1)
	{
		get_wall_dist(ray);
	}
	if (ray->side == 0)
		ray->fix_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->fix_dist = (ray->side_dist_y - ray->delta_dist_y);
}

int	get_color(t_img *img, int x, int y)
{
	// printf("%d %d \n", x ,y );
	return (*(int *)(img->addr + (y * img->line_len + x * (img->bpp / 8))));
}

void draw(t_ray *ray, int x, int y, t_img img, t_data *data)
{
	int	color;

	color = get_color(&img, ray->text_x, ray->text_y);
	my_mlx_pixel_put(&data->img, x, y, color);
}

void	get_text(t_ray *ray, t_player *player);


void	draw_game(t_ray *ray, int x, t_data *data, t_player *player)
{
	int	y;

	y = 0;
	while (y != ray->start_h)
			my_mlx_pixel_put(&data->img, x, y++, 0x0a6cc7);								
	while (y < ray->end_h)
	{
		// get_text(ray, player);
		ray->tex_pos += ray->step;
		// ray->text_y = (int)ray->tex_pos & (ray->hauteur - 1);
		ray->text_y = (y * 2 - HEIGHT + ray->hauteur) * (50 / 2) / ray->hauteur;
		// if (ray->side == 1 && player->dir_y < 0)
		// 	printf("hello 111111\n");
		// printf("%d %f\n", ray->side, player->dir_y);
		if (ray->side == 1 && ray->ray_dir_y < 0)
			// my_mlx_pixel_put(&data->img, x, y, 0xf2);
			draw(ray, x, y, ray->south, data);
		else if (ray->side == 1 && ray->ray_dir_y >= 0)
			// my_mlx_pixel_put(&data->img, x, y, 0xf2);
			draw(ray, x, y, ray->north, data);
		else if (ray->side == 0 && ray->ray_dir_x < 0)
			// my_mlx_pixel_put(&data->img, x, y, 0xb1b5b2);
			draw(ray, x, y, ray->west, data);
		else if (ray->side == 0 && ray->ray_dir_x >= 0)
			draw(ray, x, y, ray->east, data);
			// my_mlx_pixel_put(&data->img, x, y, 0xb1b5b2);
		y++;
	}
	while (y < HEIGHT - 1)
		my_mlx_pixel_put(&data->img, x, y++, 0x084a1a);
	(void)player;
}

void	get_text(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->fix_dist * ray->ray_dir_y;
	else
		ray->wall_x = player->pos_x + ray->fix_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->text_x = (ray->wall_x *(TEXT_WIDTH));
	// printf("text x %d\n", ray->text_x);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->text_x = TEXT_WIDTH - ray->text_x - 1;
	else if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->text_x =  TEXT_WIDTH - ray->text_x - 1;
	ray->step = 1.0 * TEXT_WIDTH / ray->hauteur;
	ray->tex_pos = (ray->start_h - HEIGHT / 2 + ray->hauteur / 2) * ray->step;
	// printf("%d %d %f\n", ray->start_h, ray->hauteur, ray->step);
	// ray->text_y = (int)ray->tex_pos & (ray->hauteur - 1);
}
int	make_raycasting(t_ray *ray, t_data *data, t_player *player)
{
	printf("boby\n");
	int	x;
	// int	y;

	x = 0;
	ray->width = WIDTH;
	while (x < ray->width)
	{
		// printf("x = %d\n", x);
		
		init_ray(ray, WIDTH, x, player);
		dda(ray);
		
		ray->hauteur = (int)(HEIGHT / ray->fix_dist);
		ray->start_h = (-ray->hauteur) / 2 + HEIGHT / 2;	
		ray->end_h = ray->hauteur / 2 + HEIGHT / 2;
		if (ray->start_h < 0)
			ray->start_h = 0;
		if (ray->end_h >= HEIGHT)
			ray->end_h = HEIGHT - 1;
		get_text(ray, player);
		draw_game(ray, x, data, player);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);	
	return (0);
}
void	init_texture(t_ray *ray, t_data data)
{
	ray->north = ft_image_from_xpm(data, "textures/tree.xpm", 50, 50);
	ray->south = ft_image_from_xpm(data, "textures/grass.xpm", 50, 50);
	ray->east = ft_image_from_xpm(data, "textures/exit.xpm", 50, 50);
	ray->west = ft_image_from_xpm(data, "textures/player.xpm", 50, 50);
}
t_ray	ray;
t_data		data;

int main()
{
	// t_data		data;
	// t_ray		ray;
	t_player	player;
	
	init_player(&player);
	init_mlx(&data);
	init_texture(&ray, data);
	while (1)
	{
	make_raycasting(&ray, &data, &player);
	mlx_hook(data.win, KeyPress, KeyPressMask, &ft_keypress, &player);
	mlx_hook(data.win, 17, 0, &ft_exit, &data);
	mlx_loop(data.mlx);
	}
	mlx_destroy_image(data.mlx, data.img.mlx_img);
	mlx_destroy_display(data.mlx);
	free(data.mlx);	
}
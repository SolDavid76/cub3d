/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:43:47 by ennollet          #+#    #+#             */
/*   Updated: 2023/08/03 13:01:04 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <math.h>
# include "../srcs/minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <stdlib.h>
# include <X11/X.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
#include "parsing.h"
# define HEIGHT 720
# define WIDTH 1280
# define TEXT_WIDTH 50

typedef struct s_img
{
	void	*ptr;
	char	*pxl;
	int		bpp;
	int		len;
	int		endian;
}			t_img;

typedef struct s_data
{
	char	**map;
	t_img	*north;
	t_img	*south;
	t_img	*west;
	t_img	*east;
	char	*floor;
	char	*sky;
}			t_data;

typedef struct s_win
{
	void	*mlx;
	void	*ptr;
	int		width;
	int		height;
	t_img	frame;
	t_img	minimap;
	t_data	*data;
}			t_win;

typedef	struct s_player
{
// position de depart cam
	double	pos_x;
	double	pos_y;
	// vecteur de direction
	double	dir_x;
	double	dir_y;
	// vecteur du plan de projection
	double	plane_x;
	double	plane_y;
	double	rot_speed;
}	t_player;

typedef	struct s_ray
{
	t_win	*win;
	// t_player	*player;
	// position de la colonne par rapport au centre
	double		camera_x; 
	// direction du rayon sur x et y
	double	ray_dir_x;
	double	ray_dir_y;
	// case de la camera
	int		map_x;
	int		map_y;
	// longueur du rayon
	double	side_dist_x;
	double	side_dist_y;
	// longueur du rayon entre chaque intersection
	double	delta_dist_x;
	double	delta_dist_y;
	// direction du vecteur sur X et Y (1 ou -1)
	int		step_x;
	int		step_y;
	// flag pour les murs
	int		hit;
	// orientation du mur
	int		side;
	// distance corrige pour eviter la vue de poisson
	double	fix_dist;
	// savoir ou commence sol/mur/plafond
	int		hauteur;
	int		start_h;
	int		end_h;
	double	width;
	// calculer les position dans les textures
	double	wall_x;
	int		text_x;
	int		text_y;
	double	step;
	double	tex_pos;
	// les 4 textures
	t_img	north;
	t_img	south;
	t_img	west;
	t_img	east;

}	t_ray;

typedef struct s_game
{
	t_win		win;
	t_player	player;
	t_ray		ray;
}				t_game;

void	past_img_to_frame(t_img frame, t_img img, int x, int y);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int	init_mlx(t_data *data);
int	make_raycasting(t_ray *ray, t_win *wim, t_player *player);
t_win	parsing(char *path);

void	mini_map(t_win *win, t_player *player);

/* graphics.c */
t_win	init_window(void);
t_img	*ft_img(void *mlx, char *path, int width, int height);


#endif
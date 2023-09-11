/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:43:47 by ennollet          #+#    #+#             */
/*   Updated: 2023/09/11 16:40:48 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <math.h>
# include "../srcs/minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <stdlib.h>
# include <fcntl.h>
# include <X11/X.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# define HEIGHT 720
# define WIDTH 1280
# define M_SPEED 0.01
# define P_SPEED 0.04
# define R_SPEED 0.02

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_RIGHT 65363
# define KEY_LEFT 65361
# define KEY_SHIFT 65505
# define KEY_SPACE 32
# define KEY_CTRL 65507
# define KEY_TAB 65289

typedef struct s_coords
{
	int	x;
	int	y;
}		t_coords;

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}					t_list;

typedef struct s_img
{
	void	*ptr;
	char	*pxl;
	int		bpp;
	int		len;
	int		width;
	int		height;
	int		endian;
}			t_img;

typedef struct s_data
{
	char	**map;
	t_img	*north;
	t_img	*south;
	t_img	*west;
	t_img	*east;
	int		floor;
	int		sky;
	double	spawn_x;
	double	spawn_y;
	char	spawn_dirr;
}			t_data;

typedef struct s_win
{
	void	*mlx;
	void	*ptr;
	int		width;
	int		height;
	t_img	frame;
	t_img	*mini_map;
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

typedef	struct s_hook
{
	int	hook_echap;
	int	hook_w;
	int	hook_a;
	int	hook_s;
	int	hook_d;
	int	hook_rotate_r;
	int	hook_rotate_l;
	int	hook_jump;
	int	hook_crouch;
	int	hook_sprint;
	int	hook_tab;
}	t_hook;

typedef	struct s_ray
{
	t_win		*win;
	t_player	*player;
	t_hook		*hook;
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
	int		jump;
	int		jump_nb;
	double	width;
	// calculer les position dans les textures
	double	wall_x;
	int		text_x;
	int		text_y;
	double	step;
	double	tex_pos;
	double		speed;
	int		pause;

}	t_ray;

typedef struct s_game
{
	t_win		win;
	t_player	player;
	t_ray		ray;
}				t_game;

/* utils.c */
int		ft_strlen(char *str);
int		ft_strchr(char *str, char c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strdup(char *str);
int		ft_strslen(char **strs);
char	**ft_strsdup(char **strs);
int		ft_strschr(char **strs, char c);

/* lst.c */
t_list	*ft_lstnew(char *str);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	*ft_lst_free(t_list	*lst);
int		ft_lst_maxlen(t_list *lst);

/* getters.c */
t_list	*get_infos(int fd);
int		get_rgb(char *str);
char	*mapping_aux(char *str, int len);
char	**mapping(t_list *lst);
void	get_textures(t_data *data, t_list *lst, void *mlx);

/* data.c */
t_data	*init_data(void);
t_data	*fill_data(t_data *data);

/* free.c */
void	ft_exit(char *msg);
void	free_tab(char **ptr);
void	free_img(t_img *img, void *mlx);
void	free_win(t_win *win, char *msg);

/* path_finding.c */
int		path_finding_start(char **map);
int		path_finding_aux_check(char **map, int y, int x);
int		path_finding_aux(char **map, int x, int y);
int		path_finding_verif(char **map);
int		path_finding(t_win *win, char **map);

/* graphics.c */
t_win	*init_window(void);
t_img	*ft_img(void *mlx, char *path);
t_img	*init_minimap(void *mlx, char **map);
void	past_img_to_frame(t_img frame, t_img img, int x, int y);

/* mini_map.c */
void	mini_map_aux(t_img *mini_map, t_coords coords, char **map, int color);
void	mini_map(t_win *win, t_player *player, char **map);

/* parsing.c */
int		ft_lst_maxlen(t_list *lst);
int		space(char *str, int x);
char	*ft_strjoin_char(char *str, char c);
t_win	*parsing(char *path);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int	init_mlx(t_data *data);
int	make_raycasting(t_ray *ray);

void	dda(t_ray *ray);
void	get_wall_dist(t_ray *ray);
void	init_ray(t_ray *ray, int width, int x, t_player *player);
void	draw_game(t_ray *ray, int x, t_win *win, t_player *player);
void	init_ray(t_ray *ray, int width, int x, t_player *player);

// int	ft_keypress(int keycode, t_ray *ray);
int	ft_keypress(int keycode, t_hook *hook);
int	ft_mlx_exit(t_ray *ray);

double	ft_abs(double x);


void	exec_hook(t_ray *ray, t_hook *hook);
int	ft_key_release(int keycode, t_hook *hook);
void	ft_rotate(t_player *pl, double rt_spd);

t_hook	*init_hook(t_hook *hook);
void	init_dir(t_player *player, t_ray *ray);
t_player	*init_player(t_player *player, t_ray *ray);
void	init_struct(t_ray *ray);
t_player	*init_struct_player(t_player *player);

void	select_speed(t_ray *ray);
void	crouch(t_ray *ray);
void	jump(t_ray *ray);
void	a_and_d(t_ray *ray, t_player *player, int sign);
void	w_and_s(t_ray *ray, t_player *player, int sign);
void	ft_rotate(t_player *pl, double rt_spd);

void	frame_jump(t_ray *ray);
int	hitbox_player_y(t_ray *ray, t_player *p, double x, double y);
int	hitbox_player_x(t_ray *ray, t_player *p, double x, double y);











#endif
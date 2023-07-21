/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:57:57 by djanusz           #+#    #+#             */
/*   Updated: 2023/07/21 13:28:45 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "./minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
	t_img	north;
	t_img	south;
	t_img	west;
	t_img	east;
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
	t_data	data;
}			t_win;

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}					t_list;

typedef struct s_pars
{
	t_list	*lst;
	char	**map;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*floor;
	char	*sky;
}			t_pars;

/* lst.c */
t_list	*ft_lstnew(char *str);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	*ft_lst_free(t_list	*lst);

/* graphics.c */
t_win	create_window(void);
t_img	ft_img(void *mlx, char *path, int width, int height);

#endif
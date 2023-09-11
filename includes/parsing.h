/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:57:57 by djanusz           #+#    #+#             */
/*   Updated: 2023/09/11 14:23:50 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../srcs/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "cube.h"

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

/* lst.c */
t_list	*ft_lstnew(char *str);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	*ft_lst_free(t_list	*lst);

/* main.c */
int		ft_strlen(char *str);
void	ft_exit(char *msg);

#endif
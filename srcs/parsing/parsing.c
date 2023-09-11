/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:56:08 by djanusz           #+#    #+#             */
/*   Updated: 2023/09/11 16:34:58 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	*ft_strjoin_char(char *str, char c)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str && str[i])
		res[j++] = str[i++];
	res[j++] = c;
	res[j] = '\0';
	if (str)
		free(str);
	return (res);
}

int	space(char *str, int x)
{
	int	i;

	i = 0 + x;
	while (str[i] && ((9 <= str[i] && str[i] <= 13) || str[i] == 32))
		i++;
	return (i);
}

int	ft_lst_maxlen(t_list *lst)
{
	int	res;

	res = 0;
	while (lst)
	{
		if (res < ft_strlen(lst->str))
			res = ft_strlen(lst->str);
		lst = lst->next;
	}
	return (res);
}

t_win	*parsing(char *path)
{
	t_win	*win;

	if (!path || ft_strcmp((path + ft_strlen(path) - 4), ".cub"))
		ft_exit("Path doesn't have \".cub\" extension\n");
	win = init_window();
	win->data = init_data();
	get_textures(win->data, get_infos(open(path, O_RDONLY)), win->mlx);
	win->mini_map = init_minimap(win->mlx, win->data->map);
	if (!win->data->north || !win->data->south || !win->data->west
		|| !win->data->east || win->data->floor == -1 || win->data->sky == -1)
		free_win(win, "Something went wrong\n");
	if (path_finding(win, ft_strsdup(win->data->map)))
		free_win(win, "Something went wrong\n");
	win->data = fill_data(win->data);
	return (win);
}

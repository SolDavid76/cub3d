/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:06:49 by djanusz           #+#    #+#             */
/*   Updated: 2023/09/11 16:34:45 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_list	*get_infos(int fd)
{
	t_list	*lst;
	char	*str;
	char	buf;
	int		n;

	n = 1;
	lst = NULL;
	if (fd == -1)
		ft_exit("Wrong path\n");
	while (n)
	{
		buf = '\0';
		str = NULL;
		while (n != 0 && buf != '\n')
		{
			str = ft_strjoin_char(str, buf);
			n = read(fd, &buf, 1);
		}
		if (str && str[0])
			ft_lstadd_back(&lst, ft_lstnew(str));
		else
			free(str);
	}
	return (close(fd), lst);
}

int	get_rgb(char *str)
{
	int	res;
	int	tmp;
	int	i;

	i = 0;
	res = 0;
	while (str[i])
	{
		tmp = 0;
		while ('0' <= str[i] && str[i] <= '9')
			tmp = (tmp * 10) + (str[i++] - '0');
		if (tmp < 0 || 255 < tmp || (str[i] && str[i] != ','))
			return (-1);
		res = (res * 256) + tmp;
		while (str[i] == ' ' || str[i] == ',')
			i++;
	}
	return (res);
}

char	*mapping_aux(char *str, int len)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		ft_exit("NOT ENOUGH MEMORY\n");
	i = -1;
	while (str[++i])
		res[i] = str[i];
	while (i < len)
		res[i++] = ' ';
	res[i] = '\0';
	return (res);
}

char	**mapping(t_list *lst)
{
	char	**res;
	int		len;
	int		i;

	res = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!res)
		ft_exit("NOT ENOUGH MEMORY\n");
	i = 0;
	len = ft_lst_maxlen(lst);
	while (lst)
	{
		res[i++] = mapping_aux(lst->str, len);
		lst = lst->next;
	}
	res[i] = NULL;
	return (res);
}

void	get_textures(t_data *data, t_list *lst, void *mlx)
{
	t_list	*tmp;

	tmp = lst;
	while (lst)
	{
		if (!ft_strncmp(lst->str, "NO", 2))
			data->north = ft_img(mlx, lst->str + space(lst->str, 2));
		else if (!ft_strncmp(lst->str, "SO", 2))
			data->south = ft_img(mlx, lst->str + space(lst->str, 2));
		else if (!ft_strncmp(lst->str, "WE", 2))
			data->west = ft_img(mlx, lst->str + space(lst->str, 2));
		else if (!ft_strncmp(lst->str, "EA", 2))
			data->east = ft_img(mlx, lst->str + space(lst->str, 2));
		else if (!ft_strncmp(lst->str, "F", 1))
			data->floor = get_rgb(lst->str + space(lst->str, 1));
		else if (!ft_strncmp(lst->str, "C", 1))
			data->sky = get_rgb(lst->str + space(lst->str, 1));
		else
			break ;
		lst = lst->next;
	}
	data->map = mapping(lst);
	ft_lst_free(tmp);
}

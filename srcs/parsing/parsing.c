/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:56:08 by djanusz           #+#    #+#             */
/*   Updated: 2023/07/25 15:32:29 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strslen(char **strs)
{
	int	i;
	
	if (!strs)
		return (0);
	i = 0;
	while (strs[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strdup(char *str)
{
	char	*res;
	int		i;

	if (!str)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		exit(1);
	i = -1;
	while (str[++i])
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}

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

int	ft_atoi(char *str)
{
	int	sign;
	int	res;
	int	i;

	i = 0;
	res = 0;
	sign = 1;
	if (!str)
		return (0);
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	return (sign * res);
}

void	*free_tab(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (NULL);
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (NULL);
}

void	ft_exit(char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	exit(0);
}

t_list	*get_infos(int fd)
{
	t_list	*lst;
	char	*str;
	char	buf;
	int		n;

	n = 1;
	lst = NULL;
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
	close (fd);
	return (lst);
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
	while (lst)
	{
		if (!ft_strncmp(lst->str, "NO", 2))
			data->north = ft_img(mlx, lst->str + space(lst->str, 2), 50, 50);
		else if (!ft_strncmp(lst->str, "SO", 2))
			data->south = ft_img(mlx, lst->str + space(lst->str, 2), 50, 50);
		else if (!ft_strncmp(lst->str, "WE", 2))
			data->west = ft_img(mlx, lst->str + space(lst->str, 2), 50, 50);
		else if (!ft_strncmp(lst->str, "EA", 2))
			data->east = ft_img(mlx, lst->str + space(lst->str, 2), 50, 50);
		else if (!ft_strncmp(lst->str, "F", 1))
			data->floor = ft_strdup(lst->str + space(lst->str, 1));
		else if (!ft_strncmp(lst->str, "C", 1))
			data->sky = ft_strdup(lst->str + space(lst->str, 1));
		else
			break ;
		lst = lst->next;
	}
	data->map = mapping(lst);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		ft_exit("NOT ENOUGH MEMORY\n");
	data->map = NULL;
	data->north = NULL;
	data->south = NULL;
	data->west = NULL;
	data->east = NULL;
	data->floor = NULL;
	data->sky = NULL;
	return (data);
}

void	free_img(t_img *img, void *mlx)
{
	if (img)
		mlx_destroy_image(mlx, img->ptr);
	free(img);
}

void	free_win(t_win win, char *msg)
{
	mlx_destroy_image(win.mlx, win.frame.ptr);
	free_tab(win.data->map);
	free_img(win.data->north, win.mlx);
	free_img(win.data->south, win.mlx);
	free_img(win.data->west, win.mlx);
	free_img(win.data->east, win.mlx);
	free(win.data->floor);
	free(win.data->sky);
	free(win.data);
	mlx_destroy_display(win.mlx);
	free(win.mlx);
	ft_exit(msg);
}

char	**ft_strsdup(char **strs)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (ft_strslen(strs) + 1));
	if (!res)
		ft_exit("NET ENOUGH MEMORY\n");
	i = -1;
	while (strs[++i])
		res[i] = ft_strdup(strs[i]);
	res[i] = NULL;
	return (res);
}

int	ft_strchr(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (i);
		i++;
	}
	return (0);
}

int	ft_strschr(char **strs, char c)
{
	int	i;

	if (!strs)
		return (0);
	i = 0;
	while (strs[i])
	{
		if (ft_strchr(strs[i], c))
			return (i);
		i++;
	}
	return (0);
}

int	path_finding_start(char **map)
{
	int	res;
	int	i;
	int	j;

	i = 0;
	res = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				map[i][j] = 'X';
				res++;
			}
			j++;
		}
		i++;
	}
	if (res != 1)
		free_tab(map);
	return (res);
}

int	path_finding_aux(char **map, int x, int y)
{
	int	res;
	int	i;

	i = 1;
	res = 0;
	while (x + i < ft_strlen(map[y]) && map[y][x + i] != '1' && map[y][x + i] != 'X')
		map[y][x + i++] = 'X';
	res += i - 1;
	i = 1;
	while (x - i >= 0 && map[y][x - i] != '1' && map[y][x - i] != 'X')
		map[y][x - i++] = 'X';
	res += i - 1;
	i = 1;
	while (y + i < ft_strslen(map) && map[y + i][x] != '1' && map[y + i][x] != 'X')
		map[y + i++][x] = 'X';
	res += i - 1;
	i = 1;
	while (y - i >= 0 && map[y - i][x] != '1' && map[y - i][x] != 'X')
		map[y - i++][x] = 'X';
	res += i - 1;
	return (res);
}

int	path_finding_verif(char **map)
{
	int	i;

	i = 0;
	if (ft_strchr(map[i], 'X'))
		return (free_tab(map), 1);
	while (map[i + 1])
	{
		if (map[i][0] == 'X' || map[i][ft_strlen(map[i]) - 1] == 'X')
			return (free_tab(map), 1);
		i++;
	}
	if (ft_strchr(map[i], 'X'))
		return (free_tab(map), 1);
	return (free_tab(map), 0);
}

void	ft_printmap(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		write(1, map[i], ft_strlen(map[i]));
		write(1, "\n", 1);
		i++;
	}
	write(1, "----------\n", 11);
}

int	path_finding(t_win win, char **map)
{
	int	i;
	int	j;
	int	n;

	if (path_finding_start(map) != 1)
		free_win(win, "Wrong number of player spawn\n");
	n = 1;
	while (n)
	{
		ft_printmap(map);
		n = 0;
		i = -1;
		while (map[++i])
		{
			j = -1;
			while (map[i][++j])
			{
				if (map[i][j] == 'X')
					n += path_finding_aux(map, j, i);
			}
		}
	}
	return (path_finding_verif(map));
}

void	ft_printlst(t_list *lst)
{
	write(1, "----------\n", 11);
	while (lst)
	{
		write(1, lst->str, ft_strlen(lst->str));
		write(1, "\n", 1);
		lst = lst->next;
	}
	write(1, "----------\n", 11);
}

t_win	parsing(char *path)
{
	t_win	win;
	t_list	*lst;
	int		fd;

	if (!path || ft_strcmp((path + ft_strlen(path) - 4), ".cub"))
		ft_exit("error: path doesn't have \".cub\" extension\n");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit("error: wrong path\n");
	lst = get_infos(fd);
	win = init_window();
	win.data = init_data();
	get_textures(win.data, lst, win.mlx);
	// ft_printlst(lst);
	ft_lst_free(lst);
	// ft_printmap(win.data->map);
	if (!win.data->north || !win.data->south || !win.data->west
		|| !win.data->east || !win.data->floor || !win.data->sky)
		free_win(win, "Something went wrong with textures paths\n");
	if (path_finding(win, ft_strsdup(win.data->map)))
		free_win(win, "Something went wrong with the map\n");
	return (win);
}

void	past_img_to_frame(t_img frame, t_img img, int x, int y)
{
	char	*dst;
	char	*src;
	int		i;
	int		j;
	int		p;

	i = 0;
	while (i < 50)
	{
		j = 0;
		while (j < 50)
		{
			src = img.pxl + (i * img.len + j * (img.bpp / 8));
			dst = frame.pxl + ((i + y) * frame.len + (j + x) * (frame.bpp / 8));
			p = 0;
			while (p < 4)
			{
				dst[p] = src[p];
				p++;
			}
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_win	win;

	(void)ac;
	win = parsing(av[1]);
	win.ptr = mlx_new_window(win.mlx, win.width, win.height, "cub3D");
	past_img_to_frame(win.frame, *win.data->north, 0, 0);
	past_img_to_frame(win.frame, *win.data->south, 100, 0);
	past_img_to_frame(win.frame, *win.data->west, 200, 0);
	past_img_to_frame(win.frame, *win.data->east, 300, 0);
	mlx_put_image_to_window(win.mlx, win.ptr, win.frame.ptr, 0, 0);
	mlx_loop(win.mlx);
}

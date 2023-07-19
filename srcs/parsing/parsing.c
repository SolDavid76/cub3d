/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:56:08 by djanusz           #+#    #+#             */
/*   Updated: 2023/07/19 18:25:40 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
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

void	*ft_free_tab(char **ptr)
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

void	ft_pars_exit(t_pars *pars, char *msg)
{
	if (pars)
	{
		ft_lst_free(pars->lst);
		ft_free_tab(pars->map);
		free(pars->north);
		free(pars->south);
		free(pars->west);
		free(pars->east);
		free(pars->floor);
		free(pars->sky);
		free(pars);
	}
	if (msg)
		write(2, msg, ft_strlen(msg));
	exit(0);
}

void	get_infos(t_pars *pars, char *path)
{
	char	*str;
	char	buf;
	int		fd;
	int		n;

	n = 1;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_pars_exit(pars, "error: wrong path\n");
	while (n)
	{
		str = NULL;
		while (n)
		{
			n = read(fd, &buf, 1);
			if (n == 0 || buf == '\n')
				break ;
			str = ft_strjoin_char(str, buf);
		}
		if (str)
			ft_lstadd_back(&pars->lst, ft_lstnew(str));
	}
	close (fd);
}

int	whitespace(char *str, int x)
{
	int	i;

	i = 0 + x;
	while (str[i] && ((9 <= str[i] && str[i] <= 13) || str[i] == 32))
		i++;
	return (i);
}

void	mapping(t_pars *pars, t_list *lst)
{
	int	i;

	pars->map = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!pars->map)
		ft_pars_exit(pars, "NOT ENOUGH MEMORY\n");
	i = 0;
	while (lst)
	{
		pars->map[i++] = ft_strdup(lst->content);
		lst = lst->next;
	}
	pars->map[i] = NULL;
}

void	get_textures_path(t_pars *pars)
{
	t_list	*lst;

	lst = pars->lst;
	while (lst)
	{
		if (!ft_strncmp(lst->content, "NO", 2))
			pars->north = ft_strdup(lst->content + whitespace(lst->content, 2));
		else if (!ft_strncmp(lst->content, "SO", 2))
			pars->south = ft_strdup(lst->content + whitespace(lst->content, 2));
		else if (!ft_strncmp(lst->content, "WE", 2))
			pars->west = ft_strdup(lst->content + whitespace(lst->content, 2));
		else if (!ft_strncmp(lst->content, "EA", 2))
			pars->east = ft_strdup(lst->content + whitespace(lst->content, 2));
		else if (!ft_strncmp(lst->content, "F", 1))
			pars->floor = ft_strdup(lst->content + whitespace(lst->content, 1));
		else if (!ft_strncmp(lst->content, "C", 1))
			pars->sky = ft_strdup(lst->content + whitespace(lst->content, 1));
		else
			break ;
		lst = lst->next;
	}
	mapping(pars, lst);
	pars->lst = ft_lst_free(pars->lst);
}

t_pars	*pars_init(void)
{
	t_pars	*pars;

	pars = malloc(sizeof(t_pars));
	if (!pars)
		ft_pars_exit(NULL, "NOT ENOUGH MEMORY\n");
	pars->map = NULL;
	pars->lst = NULL;
	pars->north = NULL;
	pars->south = NULL;
	pars->west = NULL;
	pars->east = NULL;
	pars->floor = NULL;
	pars->sky = NULL;
	return (pars);
}

t_pars	*parsing(char *path)
{
	t_pars	*pars;

	if (!path || ft_strcmp((path + ft_strlen(path) - 4), ".cub"))
		ft_pars_exit(NULL, "error: path doesn't have \".cub\" extension\n");
	pars = pars_init();
	get_infos(pars, path);
	get_textures_path(pars);
	return (pars);
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
}

int	main(int ac, char **av)
{
	t_pars	*pars;

	(void)ac;
	pars = parsing(av[1]);
	ft_printmap(pars->map);
	printf("NORTH = \"%s\"\n", pars->north);
	printf("SOUTH = \"%s\"\n", pars->south);
	printf("WEST = \"%s\"\n", pars->west);
	printf("EAST = \"%s\"\n", pars->east);
	printf("F = \"%s\"\n", pars->floor);
	printf("C = \"%s\"\n", pars->sky);
	ft_pars_exit(pars, "exit\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanusz <djanusz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:12:50 by djanusz           #+#    #+#             */
/*   Updated: 2023/09/11 16:34:31 by djanusz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
	data->floor = -1;
	data->sky = -1;
	return (data);
}

t_data	*fill_data(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				data->spawn_x = i;
				data->spawn_y = j;
				data->spawn_dirr = data->map[i][j];
				data->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (data);
}

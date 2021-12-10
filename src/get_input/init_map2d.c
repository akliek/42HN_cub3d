/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:55:58 by julian            #+#    #+#             */
/*   Updated: 2021/11/19 18:46:44 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	get_map_width_height(t_data *data, char *s)
{
	int	height;
	int	i;

	i = -1;
	data->map.width = 0;
	while (s[++i] != '\0')
		if (s[i] == '\n')
			data->map.width++;
	data->map.width++;
	height = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\n' && s[i] != '\0')
		{
			height++;
			i++;
		}
		if (data->map.height < height)
			data->map.height = height;
		height = 0;
		if (s[i] == '\n')
			i++;
	}
}

static void	init_map2d_helper(t_data *data)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (y < data->map.width)
	{
		x = 0;
		while (data->map.d1[i] != '\n' && data->map.d1[i] != '\0')
			data->map.d2[y][x++] = data->map.d1[i++];
		while (x < data->map.height)
			data->map.d2[y][x++] = ' ';
		if (data->map.d1[i] == '\n')
			i++;
		y++;
	}
}

int	init_map2d(t_data *data)
{
	int	y;

	get_map_width_height(data, data->map.d1);
	data->map.d2 = (char **)malloc(sizeof(char *) * data->map.width);
	if (data->map.d2 == NULL)
	{
		printf("Error\n");
		return (printf("Memory allocation failed\n"));
	}
	y = -1;
	while (++y < data->map.width)
	{
		data->map.d2[y] = (char *)malloc(sizeof(char) * data->map.height);
		if (data->map.d2[y] == NULL)
		{
			ft_free_array(data->map.d2);
			printf("Error\n");
			return (printf("Memory allocation failed\n"));
		}
	}
	init_map2d_helper(data);
	return (SUCCESS);
}

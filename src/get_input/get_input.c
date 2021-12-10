/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:45:22 by jludt             #+#    #+#             */
/*   Updated: 2021/11/20 19:04:15 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	test_general(int argc, char *argv[])
{
	int	in;

	if (argc != 2)
	{
		printf("Error\n");
		printf("Program needs scene description file with .cub extension\n");
		printf(YELLOW"Usage: "RESET);
		return (printf("./cub3D .cub_file\n"));
	}
	if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4))
	{
		printf("Error\n");
		printf("Scene description file must have .cub extension\n");
		printf(YELLOW"Usage: "RESET);
		return (printf("./cub3D .cub_file\n"));
	}
	in = open(argv[1], O_RDONLY);
	if (in < 0)
	{
		printf("Error\n");
		return (printf("%s: %s\n", strerror(errno), argv[1]));
	}
	close(in);
	return (SUCCESS);
}

static void	substitute_chars(t_data *data)
{
	int	y;
	int	x;

	x = -1;
	while (++x < data->map.width)
	{
		y = -1;
		while (++y < data->map.height)
		{
			if (data->map.d2[x][y] == ' ' || data->map.d2[x][y] == 'N' \
				|| data->map.d2[x][y] == 'E' | data->map.d2[x][y] == 'S' \
				|| data->map.d2[x][y] == 'W')
				data->map.d2[x][y] = '0';
		}
	}	
}

static void	fill_world_map(t_data *data)
{
	int	y;
	int	x;

	x = -1;
	while (++x < data->map.width)
	{
		y = -1;
		while (++y < data->map.height)
			data->world_map[x][y] = data->map.d2[x][y] - 48;
	}
}

static int	update_map(t_data *data)
{
	int	x;

	substitute_chars(data);
	data->world_map = (int **)malloc(sizeof(int *) * data->map.width);
	if (data->world_map == NULL)
	{
		ft_free_array(data->map.d2);
		return (printf("Error\nMemory allocation failed\n"));
	}
	x = -1;
	while (++x < data->map.width)
	{
		data->world_map[x] = (int *)malloc(sizeof(int) * data->map.height);
		if (data->world_map[x] == NULL)
		{
			ft_free_array(data->map.d2);
			printf("Error\n");
			return (printf("Memory allocation failed\n"));
		}
	}
	fill_world_map(data);
	return (SUCCESS);
}

int	get_input(t_data *data, int argc, char *argv[])
{
	if (test_general(argc, argv))
		return (FAILURE);
	if (get_map_look(data, argv[1]))
		return (FAILURE);
	if (update_map(data))
		return (FAILURE);
	return (SUCCESS);
}

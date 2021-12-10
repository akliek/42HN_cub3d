/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_look.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:45:57 by julian            #+#    #+#             */
/*   Updated: 2021/11/22 15:39:44 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	norm_helper2(t_data *data)
{
	if (check_map_for_invalid_char(data, data->map.d1))
	{
		free(data->map.d1);
		free_path_textures(data);
		return (FAILURE);
	}
	if (init_map2d(data))
	{
		free(data->map.d1);
		free_path_textures(data);
		return (FAILURE);
	}
	free(data->map.d1);
	if (is_map_valid(data))
	{
		free_path_textures(data);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	gnl(char **str, int in)
{
	free((*str));
	(*str) = NULL;
	(*str) = get_next_line(in);
	return (SUCCESS);
}

static int	check_info(t_data *data, char **str, int in)
{
	if ((ft_strncmp((*str), "NO ", 3) && ft_strncmp((*str), "SO ", 3) \
			&& ft_strncmp((*str), "WE ", 3) && ft_strncmp((*str), "EA ", 3) \
			&& ft_strncmp((*str), "F ", 2) && ft_strncmp((*str), "C ", 2)))
	{
		if (!ft_strcmp((*str), "\n"))
			return (gnl(str, in));
		free((*str));
		free(data->map.d1);
		free_path_textures(data);
		return (printf("Error\nInvalid identifier for texture or color\n"));
	}
	else
	{
		if (fill_map_info(data, *str))
		{
			free((*str));
			free(data->map.d1);
			free_path_textures(data);
			return (FAILURE);
		}
	}
	return (gnl(str, in));
}

static int	norm_helper(t_data *data, t_valid *v, char *file, int i)
{
	if (i == 0)
	{
		v->in = open(file, O_RDONLY);
		v->str = get_next_line(v->in);
		if (!v->str)
			return (printf("Error\nEmpty .cub-file\n"));
		v->nl = 0;
		return (init_map_input(data));
	}
	else
	{
		if (norm_helper2(data))
			return (FAILURE);
		return (SUCCESS);
	}
}

int	get_map_look(t_data *data, char *file)
{
	t_valid	v;

	if (norm_helper(data, &v, file, 0) > 0)
		return (FAILURE);
	while (v.str)
	{
		if (data->map.info != 6)
		{	
			if (check_info(data, &v.str, v.in) > 0)
				return (FAILURE);
			continue ;
		}
		if (!ft_strcmp(v.str, "\n") && v.nl == 0)
		{
			gnl(&v.str, v.in);
			continue ;
		}
		if (!ft_strcmp(v.str, "\n") && v.nl == 1)
			return (printf("Error\nEmpty line in map\n"));
		v.nl = 1;
		data->map.d1 = ft_strjoin(data->map.d1, v.str);
		gnl(&v.str, v.in);
	}
	return (norm_helper(data, NULL, NULL, 1));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_to_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:10:09 by julian            #+#    #+#             */
/*   Updated: 2021/11/19 18:05:45 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	norm_helper2(t_data *data, char **input)
{
	if (!ft_strcmp(input[0], "NO"))
	{
		data->map.no = ft_strdup(input[1]);
		data->map.n_no = 1;
	}
	else if (!ft_strcmp(input[0], "SO"))
	{
		data->map.so = ft_strdup(input[1]);
		data->map.n_so = 1;
	}
	else if (!ft_strcmp(input[0], "WE"))
	{
		data->map.we = ft_strdup(input[1]);
		data->map.n_we = 1;
	}
	else if (!ft_strcmp(input[0], "EA"))
	{
		data->map.ea = ft_strdup(input[1]);
		data->map.n_ea = 1;
	}
	data->map.info++;
}

static int	norm_helper1(t_data *data, char **input)
{
	if ((!ft_strcmp(input[0], "NO") && data->map.n_no == 1)
		|| (!ft_strcmp(input[0], "SO") && data->map.n_so == 1)
		|| (!ft_strcmp(input[0], "WE") && data->map.n_we == 1)
		|| (!ft_strcmp(input[0], "EA") && data->map.n_ea == 1))
		return (FAILURE);
	else
		return (SUCCESS);
}

int	get_path_to_texture(t_data *data, char *str)
{
	char	**input;
	int		in;

	input = ft_split(str, ' ');
	if (input == NULL)
		return (printf("Error\nInput couldn't be splitted correctly"));
	if (ft_array_len(input) != 2)
		ft_free_array(input);
	if (ft_array_len(input) != 2)
		return (printf("Error\nInfo for path to texture formatted"));
	if (norm_helper1(data, input) == FAILURE)
		ft_free_array(input);
	if (norm_helper1(data, input) == FAILURE)
		return (printf("Error\nDuplication of path to texture identifier\n"));
	if (input[1][ft_strlen(input[1]) - 1] == '\n')
		input[1] = ft_strtrim(input[1], "\n");
	if (ft_strncmp(input[1] + (ft_strlen(input[1]) - 4), ".xpm", 4))
		return (printf("Error\nTexture file must have .xpm extension\n"));
	in = open(input[1], O_RDONLY);
	if (in < 0)
		return (printf("Error\n%s: %s\n", strerror(errno), input[1]));
	close(in);
	norm_helper2(data, input);
	ft_free_array(input);
	return (SUCCESS);
}

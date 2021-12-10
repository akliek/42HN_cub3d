/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:59:36 by julian            #+#    #+#             */
/*   Updated: 2021/11/22 15:38:45 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	free_path_textures(t_data *data)
{
	if (data->map.no)
		free(data->map.no);
	if (data->map.so)
		free(data->map.so);
	if (data->map.we)
		free(data->map.we);
	if (data->map.ea)
		free(data->map.ea);
}

int	init_map_input(t_data *data)
{
	data->map.info = 0;
	data->map.color_floor[3] = 0;
	data->map.color_ceiling[3] = 0;
	data->map.n_no = 0;
	data->map.n_so = 0;
	data->map.n_we = 0;
	data->map.n_ea = 0;
	data->map.d1 = (char *)malloc(sizeof(char) * 1);
	if (data->map.d1 == NULL)
		return (FAILURE);
	data->map.d1[0] = '\0';
	return (SUCCESS);
}

int	fill_map_info(t_data *data, char *str)
{
	if (!ft_strncmp(str, "F", 1) || !ft_strncmp(str, "C", 1))
		return (get_color_fc(data, str));
	if (!strncmp(str, "NO", 2) || !strncmp(str, "SO", 2)
		|| !strncmp(str, "WE", 2) || !strncmp(str, "EA", 2))
		return (get_path_to_texture(data, str));
	return (FAILURE);
}

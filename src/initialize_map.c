/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 10:46:19 by jludt             #+#    #+#             */
/*   Updated: 2021/11/23 11:42:24 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	initialize_map_norm_helper(t_data *data)
{
	if (data->map.player == 'S')
	{
		data->dir_x = 1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = -0.66;
	}
	if (data->map.player == 'W')
	{
		data->dir_x = 0;
		data->dir_y = -1;
		data->plane_x = -0.66;
		data->plane_y = 0;
	}
}

void	initialize_map(t_data *data)
{	
	if (data->map.player == 'N')
	{
		data->dir_x = -1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = 0.66;
	}
	if (data->map.player == 'E')
	{
		data->dir_x = 0;
		data->dir_y = 1;
		data->plane_x = 0.66;
		data->plane_y = 0;
	}
	initialize_map_norm_helper(data);
	data->move_speed = 0.04;
	data->rot_speed = 0.03;
	data->key.pause = 1;
	load_texture(data);
}

void	load_texture(t_data *data)
{
	t_img	img;

	load_image(data, data->texture[0], data->map.no, &img);
	load_image(data, data->texture[1], data->map.ea, &img);
	load_image(data, data->texture[2], data->map.so, &img);
	load_image(data, data->texture[3], data->map.we, &img);
}

void	load_image(t_data *data, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->img = mlx_xpm_file_to_image(data->mlx, path, \
		&img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, \
		&img->size_l, &img->endian);
	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
			texture[img->img_height * y + x] = \
				img->data[img->img_height * y + x];
	}
	mlx_destroy_image(data->mlx, img->img);
}

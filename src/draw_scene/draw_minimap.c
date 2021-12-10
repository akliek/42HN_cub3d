/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akliek <akliek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 16:45:06 by jludt             #+#    #+#             */
/*   Updated: 2021/11/22 13:27:45 by akliek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	get_squre_size(int n)
{
	int	res;
	int	value;

	if (SCREEN_HEIGHT < SCREEN_WIDTH)
		value = SCREEN_HEIGHT;
	else
		value = SCREEN_WIDTH;
	res = value / (n * 3);
	if (res < 2)
		res = 2;
	return (res);
}

static void	draw_player(t_data *data, int w, int h)
{
	int	i;
	int	j;

	i = 0;
	while (++i < w && ((int)data->pos_y * w) + i <= SCREEN_WIDTH - 1)
	{
		j = 0;
		while (++j < h && ((int)data->pos_x * h) + j <= SCREEN_HEIGHT - 1)
			my_mlx_pixel_put(data, ((int)data->pos_y * w) + i,
				((int)data->pos_x * h) + j, 0x00FF0000);
	}
}

static void	draw_map(t_data *data, int w, int h, int color)
{
	int		x;
	int		y;
	int		i;
	int		j;

	y = -1;
	while (++y < data->map.width)
	{
		x = -1;
		while (++x < data->map.height)
		{
			if (x == (int)data->pos_y && y == (int)data->pos_x)
				draw_player(data, w, h);
			if (data->world_map[y][x] > 0)
			{
				i = 0;
				while (++i < w && (x * w) + i <= SCREEN_WIDTH - 1)
				{
					j = 0;
					while (++j < h && (y * h) + j <= SCREEN_HEIGHT - 1)
						my_mlx_pixel_put(data, (x * w) + i, (y * h) + j, color);
				}
			}
		}
	}
}

void	draw_minimap(t_data *data)
{
	int	w;
	int	h;
	int	color;

	w = get_squre_size(24);
	h = get_squre_size(24);
	color = create_trgb(0, 255, 255, 255);
	draw_map(data, w, h, color);
}

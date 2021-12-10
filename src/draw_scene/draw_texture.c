/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 11:56:25 by jludt             #+#    #+#             */
/*   Updated: 2021/11/23 11:49:13 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	calc_initial_state(t_data *data, t_rc *rc)
{
	rc->camera_x = 2 * rc->x / (double)SCREEN_WIDTH - 1;
	rc->ray_dir_x = data->dir_x + data->plane_x * rc->camera_x;
	rc->ray_dir_y = data->dir_y + data->plane_y * rc->camera_x;
	rc->map_x = (int)data->pos_x;
	rc->map_y = (int)data->pos_y;
	rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
	rc->delta_dist_y = fabs(1 / rc->ray_dir_y);
	rc->hit = 0;
}

void	calc_step_and_side_dist(t_data *data, t_rc *rc)
{
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (data->pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - data->pos_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (data->pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - data->pos_y) * rc->delta_dist_y;
	}
}

void	perform_dda(t_data *data, t_rc *rc)
{
	while (rc->hit == 0)
	{
		if (rc->side_dist_x < rc->side_dist_y)
			dda_norm_helper(data, rc);
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
			if (data->world_map[rc->map_x][rc->map_y] > 0)
			{
				rc->hit = 1;
				if (rc->map_y > data->pos_y)
					rc->tex_num = 3;
				else
					rc->tex_num = 1;
			}
		}
	}
	if (rc->side == 0)
		rc->perp_wall_dist = (rc->side_dist_x - rc->delta_dist_x);
	else
		rc->perp_wall_dist = (rc->side_dist_y - rc->delta_dist_y);
}

void	calc_texturing(t_data *data, t_rc *rc)
{
	rc->line_height = ((int)(SCREEN_HEIGHT / rc->perp_wall_dist)) * 2;
	rc->draw_start = -rc->line_height / 2 + SCREEN_HEIGHT / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + SCREEN_HEIGHT / 2;
	if (rc->draw_end >= SCREEN_HEIGHT)
		rc->draw_end = SCREEN_HEIGHT - 1;
	if (rc->side == 0)
		rc->wall_x = data->pos_y + rc->perp_wall_dist * rc->ray_dir_y;
	else
		rc->wall_x = data->pos_x + rc->perp_wall_dist * rc->ray_dir_x;
	rc->wall_x -= floor((rc->wall_x));
	rc->tex_x = (int)(rc->wall_x * (double)(TEX_WIDTH));
	if (rc->side == 0 && rc->ray_dir_x > 0)
		rc->tex_x = TEX_WIDTH - rc->tex_x - 1;
	if (rc->side == 1 && rc->ray_dir_y < 0)
		rc->tex_x = TEX_WIDTH - rc->tex_x - 1;
	rc->step = 1.0 * TEX_HEIGHT / rc->line_height;
	rc->tex_pos = (rc->draw_start - SCREEN_HEIGHT / 2 \
		+ rc->line_height / 2) * rc->step;
	rc->y = rc->draw_start - 1;
}

void	draw_texture(t_data *data, t_rc *rc)
{
	while (++rc->y < rc->draw_end)
	{
		rc->tex_y = (int)rc->tex_pos & (TEX_HEIGHT - 1);
		rc->tex_pos += rc->step;
		rc->color = data->texture[rc->tex_num][TEX_HEIGHT \
			* rc->tex_y + rc->tex_x];
		if (rc->side == 1)
			rc->color /= 2;
		my_mlx_pixel_put(data, rc->x, rc->y, rc->color);
	}
}

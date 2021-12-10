/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:08:57 by julian            #+#    #+#             */
/*   Updated: 2021/11/23 11:42:36 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

# define SUCCESS		0
# define FAILURE		1

# define SCREEN_WIDTH	1024
# define SCREEN_HEIGHT	512
# define TEX_WIDTH		64
# define TEX_HEIGHT		64

# define KEY_ANSI_A		(0X00)
# define KEY_ANSI_S		(0X01)
# define KEY_ANSI_D		(0X02)
# define KEY_ANSI_W		(0X0D)
# define KEY_LEFTARROW	(0X7B)
# define KEY_RIGHTARROW	(0X7C)
# define KEY_ESCAPE		(0X35)
# define KEY_PAUSE		(0X23)

// data for raycaster
typedef struct s_rc
{
	int				x;
	int				y;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_num;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				tex_y;
	unsigned int	color;
}			t_rc;

typedef struct s_color
{
	char	**input;
	char	**rgb;
	int		i;
	int		j;
}			t_color;

typedef struct s_valid
{
	int		in;
	char	*str;
	int		nl;
}			t_valid;

typedef struct s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}			t_img;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	la;
	int	ra;
	int	esc;
	int	pause;
}			t_keys;

typedef struct s_map
{
	int		info;
	int		color_floor[4];
	int		color_ceiling[4];
	char	*no;
	int		n_no;
	char	*so;
	int		n_so;
	char	*we;
	int		n_we;
	char	*ea;
	int		n_ea;
	char	*d1;
	char	**d2;
	int		width;
	int		height;
	int		**world_map;
	char	player;
	double	player_pos_x;
	double	player_pos_y;
	double	player_view_x;
	double	player_view_y;
}			t_map;

typedef struct s_val
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;
}			t_val;

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	void	*mlx_img;
	char	*mlx_data_addr;
	int		mlx_bits_per_pixel;
	int		mlx_size_line;
	int		mlx_endian;
	int		img_width;
	int		img_height;
	t_img	img;
	t_keys	key;
	t_map	map;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	int		**world_map;
	int		texture[4][TEX_HEIGHT * TEX_WIDTH];
}			t_data;

void	initialize_map(t_data *data);
void	load_texture(t_data *data);
void	load_image(t_data *data, int *texture, char *path, t_img *img);
int		key_update(t_data *data);
int		key_press(int key, t_data *data);
int		key_release(int key, t_data *data);
int		mouse_move(int x, int y, t_data *data);
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);
void	move_forward(t_data *data);
void	move_backward(t_data *data);
int		ft_close(t_data *data);
int		create_trgb(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		draw_scene(t_data *data);
void	draw_floor(t_data *data);
void	draw_ceiling(t_data *data);
void	calc_initial_state(t_data *data, t_rc *rc);
void	calc_step_and_side_dist(t_data *data, t_rc *rc);
void	perform_dda(t_data *data, t_rc *rc);
void	calc_texturing(t_data *data, t_rc *rc);
void	draw_texture(t_data *data, t_rc *rc);
void	draw_minimap(t_data *data);
int		get_input(t_data *data, int argc, char *argv[]);
int		ft_array_len(char **array);
void	ft_free_array(char **array);
void	free_path_textures(t_data *data);
int		get_map_look(t_data *data, char *file);
int		init_map2d(t_data *data);
int		init_map_input(t_data *data);
int		fill_map_info(t_data *data, char *str);
int		get_color_fc(t_data *data, char *str);
int		get_path_to_texture(t_data *data, char *str);
int		check_map_for_invalid_char(t_data *data, char *s);
int		is_map_valid(t_data *data);
void	dda_norm_helper(t_data *data, t_rc *rc);

#endif
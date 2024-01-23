/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:21:41 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/22 23:13:30 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	clear_color_buffer(t_data *data, int color)
{
	int	pixel;

	pixel = 0;
	while (pixel < SCENE_SIZE)
	{
		data->game_color_buffer[pixel] = color;
		pixel++;
	}
}

void	init_buffer_image(t_data *cube)
{
	cube->scene->img_ptr = mlx_new_image(cube->win->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	cube->scene->addr = mlx_get_data_addr(cube->scene->img_ptr,
			&cube->scene->bpp, &cube->scene->line_length,
			&cube->scene->endian);
}

void	render_color(t_data *cube)
{
	int	x;
	int	y;

	init_buffer_image(cube);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			pixel_put(cube->scene, x, y,
				cube->game_color_buffer[(WINDOW_WIDTH * y) + x]);
			y++;
		}
		x++;
	}
	clear_color_buffer(cube, 0x000000);
	mlx_put_image_to_window(cube->win->mlx, cube->win->m_win,
		cube->scene->img_ptr, 0, 0);
	// mlx_destroy_image(cube->win->mlx, cube->scene->img_ptr);
}

// Uninitialized Values at line 76 and 77 -> rotation_angle
// PL: fixed on mappinp.c
void	player_movement(t_data *data)
{
	float	delta;
	float	delta_move;
	float	angle;
	float	updated_pos_player_x;
	float	updated_pos_player_y;

	updated_pos_player_x = data->player->pos_game->x;
	updated_pos_player_y = data->player->pos_game->y;
	delta = (float)data->player->movement.walk_direction * 4;
	delta_move = (float)data->player->movement.side_direction * 4;
	data->player->rotation_angle += (float)data->player->movement.turn_direction
		* (4 * (M_PI / 180));
	angle = data->player->rotation_angle - (M_PI / 2);
	updated_pos_player_x += cos(data->player->rotation_angle) * delta;
	updated_pos_player_y += sin(data->player->rotation_angle) * delta;
	updated_pos_player_x += cos(angle) * delta_move;
	updated_pos_player_y += sin(angle) * delta_move;
	if (has_wall(data, updated_pos_player_x, updated_pos_player_y) == false)
	{
		data->player->pos_game->x = updated_pos_player_x;
		data->player->pos_game->y = updated_pos_player_y;
	}
}

int	render_loop(t_data *cub3d)
{
	player_movement(cub3d);
	ray_casting(cub3d);
	render_walls(cub3d);
	// render_map(cub3d);
	render_color(cub3d);
	return (true);
}

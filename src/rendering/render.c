/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:21:41 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/20 22:00:28 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

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
	cube->scene->img_ptr = mlx_new_image(cube->win->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT);
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
	mlx_destroy_image(cube->win->mlx, cube->scene->img_ptr);
}

void	player_movement(t_data *data)
{
	float	move_step;
	float	side_move_step;
	float	side_angle;
	float	new_player_x;
	float	new_player_y;

	new_player_x = data->player->pos_scaled_game->x;
	new_player_y = data->player->pos_scaled_game->y;
	move_step = (float)data->player->movement.walk_direction * 4;
	side_move_step = (float)data->player->movement.side_direction * 4;
	data->player->rotation_angle += (float)data->player->movement.turn_direction
		* (4 * (M_PI / 180));
	side_angle = data->player->rotation_angle - (M_PI / 2);
	new_player_x += cos(data->player->rotation_angle) * move_step;
	new_player_y += sin(data->player->rotation_angle) * move_step;
	new_player_x += cos(side_angle) * side_move_step;
	new_player_y += sin(side_angle) * side_move_step;
	if (!has_wall(data, new_player_x, new_player_y))
	{
		data->player->pos_scaled_game->x = new_player_x;
		data->player->pos_scaled_game->y = new_player_y;
	}
}

int	render_loop(t_data *cub3d)
{
	//if (cub3d->is_running == FALSE)
		//free_resources(cub3d);
	//else
	//clock_t begin = clock();

/* here, do your time-consuming job */

		//ft_bzero(cub3d->scene->addr, WINDOW_WIDTH * WINDOW_HEIGHT * 8);
		//check is move player is working
		player_movement(cub3d);
		ray_casting(cub3d);
		mlx_clear_window(cub3d->win->mlx, cub3d->win->m_win);
		render_walls(cub3d);
	//render_map(cub3d);
		render_color(cub3d);
//	clock_t end = clock();
	//double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	//printf("\ntime %f", time_spent);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:21:41 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/15 10:14:13 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

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



int	render_loop(t_data *cub3d)
{
	//if (cub3d->is_running == FALSE)
		//free_resources(cub3d);
	//else
	{
		//check is move player is working
		ray_casting(cub3d);
		//mlx_clear_window(cub3d->win->mlx, cub3d->win->m_win);
		render_walls(cub3d);
		render_color(cub3d);

	}
	return (0);
}








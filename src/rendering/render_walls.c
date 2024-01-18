/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:19:19 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/15 15:08:02 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pixel_get(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

void	initialize_wall(t_data *data, t_wall *wall, int x)
{
	wall->projected_wall_dist = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	wall->corrected_ray_distance = data->rays[x].distance
		* cos(data->player->rotation_angle - data->rays[x].angle);
	wall->projected_wall_height = (int)((TILE_SIZE
				/ wall->corrected_ray_distance * wall->projected_wall_dist));
	wall->top_pixel = (WINDOW_HEIGHT / 2) - (wall->projected_wall_height / 2);
	wall->bottom_pixel = (WINDOW_HEIGHT / 2) + (wall->projected_wall_height
			/ 2);
	if (wall->top_pixel < 0)
		wall->top_pixel = 0;
	if (wall->bottom_pixel > WINDOW_HEIGHT)
		wall->bottom_pixel = WINDOW_HEIGHT;
	if (data->rays[x].is_up)
		wall->x_texture_offset = (int)data->rays[x].hit_y % TILE_SIZE;
	else
		wall->x_texture_offset = (int)data->rays[x].hit_x % TILE_SIZE;
}

void	draw_wall(t_data *data, t_wall wall, int x)
{
	int	y;

	y = wall.top_pixel - 1;
	while (++y < wall.bottom_pixel)
	{
		wall.distance_from_top = y +
			(wall.projected_wall_height / 2) - (WINDOW_HEIGHT / 2);
		wall.y_texture_offset = wall.distance_from_top * ((float)TILE_SIZE
				/ wall.projected_wall_height);
		if (data->rays[x].is_up == false
			&& data->rays[x].direction.is_down)
			wall.orientation = 1;
		else if (data->rays[x].is_up == false
			&& data->rays[x].direction.is_down)
			wall.orientation = 0;
		else if (data->rays[x].is_up
			&& data->rays[x].direction.is_left)
			wall.orientation = 3;
		else if (data->rays[x].is_up
			&& data->rays[x].direction.is_right)
			wall.orientation = 2;
		wall.texel_color = 200;
		//pixel_get(data->map->textures[wall.orientation].,
		//		wall.x_texture_offset, wall.y_texture_offset);

		data->game_color_buffer[(WINDOW_WIDTH * y) + x] = wall.texel_color;


		//draw_pixel(data, x, y, wall.texel_color);
	}
}

int	create_trgb(int r, int g, int b)
{
	int	colour;
	colour = r;
	colour = 256 * colour + g;
	colour = 256 * colour + b;
	return (colour);
}

void	draw_cealing(t_data *data, t_wall wall, int x)
{
	int	y;

	y = -1;
	while (++y < wall.top_pixel)
		data->game_color_buffer[(WINDOW_WIDTH * y) + x] = create_trgb(data->map->ceiling[0], data->map->ceiling[1], data->map->ceiling[2]);;
}



void	draw_floor(t_data *data, t_wall wall, int x)
{
	int	y;

	y = wall.bottom_pixel - 1;
	while (++y < WINDOW_HEIGHT)
		data->game_color_buffer[(WINDOW_WIDTH * y) + x] = create_trgb(data->map->floor[0], data->map->floor[1], data->map->floor[2]);
}

void	render_walls(t_data *cub3d)
{
	int ray_count;
	//int color;
	t_wall	wall;

	ray_count = 0;
	while (ray_count < WINDOW_WIDTH)
	{
		initialize_wall(cub3d, &wall, ray_count);
		draw_cealing(cub3d, wall, ray_count);
		draw_wall(cub3d, wall, ray_count);
		draw_floor(cub3d, wall, ray_count);
		ray_count++;
	}
}
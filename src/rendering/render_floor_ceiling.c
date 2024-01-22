/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 22:47:22 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/22 23:14:25 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_ceiling(t_data *data, t_wall wall, int x)
{
	int	y;

	y = 0;
	while (y < wall.top_pixel)
	{
		data->game_color_buffer[(WINDOW_WIDTH * y) + x]
			= create_trgb(data->map->ceiling[0], data->map->ceiling[1],
				data->map->ceiling[2]);
		y++;
	}
}

void	draw_floor(t_data *data, t_wall wall, int x)
{
	int	y;

	y = wall.bottom_pixel;
	while (y < WINDOW_HEIGHT)
	{
		data->game_color_buffer[(WINDOW_WIDTH * y) + x]
			= create_trgb(data->map->floor[0], data->map->floor[1],
				data->map->floor[2]);
		y++;
	}
}

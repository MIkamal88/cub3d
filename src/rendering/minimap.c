/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:44:51 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/15 10:13:53 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


void	draw_rect(t_data *data, t_rect rect)
{
	int	i;
	int	j;

	i = rect.x - 1;
	while (++i < rect.x + rect.width)
	{
		j = rect.y - 1;
		while (++j < rect.y + rect.height)
			data->game_color_buffer[(WINDOW_WIDTH * i) + j] =  rect.color;
	}
}


void	render_map(t_data *data)
{
	t_rect	rect;
	int		i;
	int		j;

	i = -1;
	while (++i < data->map->rows)
	{
		j = -1;
		while (++j < data->map->x_max)
		{
			rect.x = (j * TILE_SIZE) * data->minimap->scale;
			rect.y = (i * TILE_SIZE) * data->minimap->scale;
			rect.height = TILE_SIZE * data->minimap->scale;
			rect.width = TILE_SIZE * data->minimap->scale;
			if (data->map->grid[i][j].type == WALL)
				rect.color = MINIMAP_WHITE;
			else
				rect.color = MINIMAP_BLACK;
			draw_rect(data, rect);
		}
	}
}




/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 08:49:26 by m_kamal           #+#    #+#             */
/*   Updated: 2023/12/30 08:49:26 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static t_map	*init_map(void)
{
	int		i;
	t_map	*map;

	i = -1;
	map = malloc(sizeof(t_map));
	if (!map)
		ft_error(NULL, MALLOC_ERR);
	map->rows = -1;
	map->grid = ft_calloc(sizeof(t_point **), 1);
	map->textures = malloc(sizeof(t_texture *) * 4);
	while (++i < 4)
	{
		if (i < 3)
		{
			map->floor[i] = -1;
			map->ceiling[i] = -1;
		}
		map->textures[i] = malloc(sizeof(t_texture));
		map->textures[i]->path = NULL;
		map->textures[i]->cardinal = i;
	}
	return (map);
}

void	map_read(t_data *cub3d, char *filename)
{
	int		i;

	i = -1;
	cub3d->map = init_map();
	while (++i < 4)
		if (!read_textures(cub3d, filename, i))
			ft_error(cub3d, MAP_ERR);
	if (!set_floor_ceiling(cub3d, filename))
		ft_error(cub3d, MAP_ERR);
	fetch_grid(cub3d, filename);
	if (cub3d->map->rows <= 3)
		ft_error(cub3d, MAP_ERR);
	printf("map->grid[0][0]->x = %d\n", cub3d->map->grid[0][0].x);
	printf("map->grid[0][0]->y = %d\n", cub3d->map->grid[0][0].y);
}

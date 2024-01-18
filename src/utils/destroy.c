/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 08:26:12 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/06 15:35:18 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_double_ptr(void **d_ptr)
{
	int	i;

	i = -1;
	while (d_ptr[++i])
		free(d_ptr[i]);
	free(d_ptr);
}

void	free_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (map->textures[i] && map->textures[i]->path)
			free(map->textures[i]->path);
		free(map->textures[i]);
	}
	free(map->textures);
	if (map->grid)
	{
		i = -1;
		while (++i < map->rows)
			free(map->grid[i]);
	}
	free(map->grid);
	free(map);
}

int	exit_window(t_data *cub3d)
{
	if (cub3d->win)
		free_all(cub3d);
	exit(EXIT_SUCCESS);
}

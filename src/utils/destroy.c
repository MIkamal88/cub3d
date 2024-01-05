/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 08:26:12 by m_kamal           #+#    #+#             */
/*   Updated: 2023/12/29 08:26:12 by m_kamal          ###   ########.fr       */
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

void	free_all(t_data *cub3d)
{
	if (cub3d->player)
	{
		free(cub3d->player->pos_scaled);
		free(cub3d->player->pos);
		free(cub3d->player);
	}
	if (cub3d->map)
		free_map(cub3d->map);
	if (cub3d->scene)
	{
		mlx_destroy_image(cub3d->win->mlx, cub3d->scene->img_ptr);
		free(cub3d->scene);
	}
	if (cub3d->minimap)
	{
		mlx_destroy_image(cub3d->win->mlx, cub3d->minimap->img_ptr);
		free(cub3d->minimap);
	}
	if (cub3d->win)
	{
		mlx_destroy_window(cub3d->win->mlx, cub3d->win->m_win);
		mlx_destroy_display(cub3d->win->mlx);
		free(cub3d->win->mlx);
		free(cub3d->win);
	}
	free(cub3d);
}

int	exit_window(t_data *cub3d)
{
	if (cub3d->win)
		free_all(cub3d);
	exit(EXIT_SUCCESS);
}

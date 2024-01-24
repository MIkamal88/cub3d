/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 08:26:12 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/21 12:06:14 by pbalbino         ###   ########.fr       */
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

void	free_map(t_data *cub3d)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (cub3d->map->textures[i]->texture_img)
		{
			mlx_destroy_image(cub3d->win->mlx,
				cub3d->map->textures[i]->texture_img->img_ptr);
			free(cub3d->map->textures[i]->texture_img);
		}
		if (cub3d->map->textures[i] && cub3d->map->textures[i]->path)
			free(cub3d->map->textures[i]->path);
		free(cub3d->map->textures[i]);
	}
	i = -1;
	if (cub3d->map->grid)
		while (++i < cub3d->map->rows)
			free(cub3d->map->grid[i]);
	free(cub3d->map->textures);
	free(cub3d->map->grid);
	free(cub3d->map);
}

int	exit_window(t_data *cub3d)
{
	if (cub3d->win)
		free_all(cub3d);
	exit(EXIT_SUCCESS);
}

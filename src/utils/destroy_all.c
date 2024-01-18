/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 06:43:11 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/18 06:43:11 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

#ifdef __linux__

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
	mlx_destroy_image(cub3d->win->mlx, cub3d->scene->img_ptr);
	if (cub3d->scene)
		free(cub3d->scene);
	mlx_destroy_image(cub3d->win->mlx, cub3d->minimap->img_ptr);
	if (cub3d->minimap)
		free(cub3d->minimap);
	if (cub3d->win)
	{
		mlx_destroy_window(cub3d->win->mlx, cub3d->win->m_win);
		mlx_destroy_display(cub3d->win->mlx);
		free(cub3d->win->mlx);
		free(cub3d->win);
	}
	free(cub3d);
}

#elif __APPLE__

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
	mlx_destroy_image(cub3d->win->mlx, cub3d->scene->img_ptr);
	if (cub3d->scene)
		free(cub3d->scene);
	mlx_destroy_image(cub3d->win->mlx, cub3d->minimap->img_ptr);
	if (cub3d->minimap)
		free(cub3d->minimap);
	if (cub3d->win)
	{
		mlx_destroy_display(cub3d->win->mlx);
		free(cub3d->win->mlx);
		free(cub3d->win);
	}
	free(cub3d);
}

#endif

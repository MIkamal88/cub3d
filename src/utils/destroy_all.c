/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   mlx_destroy.c                                      :+:      :+:    :+:   */
/*   destroy_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 07:17:05 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/21 12:05:42 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

#if __APPLE__

void	free_all(t_data *cub3d)
{
	free(cub3d->game_color_buffer);
	if (cub3d->player)
	{
		free(cub3d->player->pos_scaled);
		free(cub3d->player->pos);
		free(cub3d->player->pos_game);
		free(cub3d->player);
	}
	if (cub3d->rays)
		free(cub3d->rays);
	if (cub3d->map)
		free_map(cub3d);
	mlx_destroy_image(cub3d->win->mlx, cub3d->scene->img_ptr);
	free(cub3d->scene);
	mlx_destroy_window(cub3d->win->mlx, cub3d->win->m_win);
	free(cub3d->win->mlx);
	free(cub3d->win);
	free(cub3d);
}

#elif __linux__

void	free_all(t_data *cub3d)
{
	free(cub3d->game_color_buffer);
	if (cub3d->player)
	{
		free(cub3d->player->pos_scaled);
		free(cub3d->player->pos);
		free(cub3d->player->pos_game);
		free(cub3d->player);
	}
	if (cub3d->rays)
		free(cub3d->rays);
	if (cub3d->map)
		free_map(cub3d);
	mlx_destroy_image(cub3d->win->mlx, cub3d->scene->img_ptr);
	free(cub3d->scene);
	mlx_destroy_window(cub3d->win->mlx, cub3d->win->m_win);
	mlx_destroy_display(cub3d->win->mlx);
	free(cub3d->win->mlx);
	free(cub3d->win);
	free(cub3d);
}

#endif

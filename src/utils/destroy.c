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

void	free_all(t_data *cub3d)
{
	if (cub3d->win)
	{
		mlx_destroy_window(cub3d->win->mlx, cub3d->win->m_win);
		mlx_destroy_display(cub3d->win->mlx);
	}
	free(cub3d->win->mlx);
	free(cub3d->win);
	free(cub3d);
}

int	exit_window(t_data *cub3d)
{
	if (cub3d->win)
		free_all(cub3d);
	exit(EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:06:53 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/15 10:14:20 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_text(t_data *cub3d)
{
	int	x;
	int	y;

	x = 1770;
	y = 20;
	mlx_string_put(cub3d->win->mlx, cub3d->win->m_win, x, y,
		TEXT_COLOR, "Press 'Esc' to close.");
	mlx_string_put(cub3d->win->mlx, cub3d->win->m_win, x, y + 20,
		TEXT_COLOR, "'W' 'A' 'S' 'D' to move.");
	mlx_string_put(cub3d->win->mlx, cub3d->win->m_win, x, y + 40,
		TEXT_COLOR, "'Q' 'E' to rotate.");
}

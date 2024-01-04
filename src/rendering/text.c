/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:06:53 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/02 18:06:53 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_text(t_data *cub3d)
{
	int	x;
	int	y;

	x = 1780;
	y = 20;
	mlx_string_put(cub3d->win->mlx, cub3d->win->m_win, x, y,
		TEXT_COLOR, "Press 'Esc' to close.");
}

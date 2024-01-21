/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 08:31:29 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/21 11:52:33 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBINDS_H
# define KEYBINDS_H

# if __APPLE__
#  include "../libs/mlx/mac/mlx.h"
#  define KEY_W	13
#  define KEY_A	0
#  define KEY_S	1
#  define KEY_D 2
#  define KEY_ESC 53
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_I 34
#  define KEY_O 31
#  define KEY_R 15

# elif __linux__
#  include "../libs/mlx/linux/mlx.h"
#  define KEY_W		119
#  define KEY_A		97
#  define KEY_S		115
#  define KEY_D		100
#  define KEY_ESC	65307
#  define KEY_UP	65362
#  define KEY_DOWN	65364
#  define KEY_LEFT	65361
#  define KEY_RIGHT	65363
#  define KEY_I		105
#  define KEY_O		111
#  define KEY_R		114

# endif

#endif

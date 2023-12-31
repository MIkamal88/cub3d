/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:51:24 by m_kamal           #+#    #+#             */
/*   Updated: 2023/12/30 15:51:24 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	clear_read(char *line, int fd)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

t_bool	valid_extension(char *file, char *ext)
{
	char	*extension;

	if (!file || !ext)
		return (FALSE);
	extension = ft_strrchr(file, '.');
	if (!extension)
		return (FALSE);
	else if (ft_strncmp(extension, ext, ft_strlen(ext)))
		return (FALSE);
	else
		return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <youness@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:23:16 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/16 23:58:50 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d.h"

// char	**get_map(char *file)
// {
// 	int		fd;
// 	char	*line;
// 	char	*tmp;
// 	char	**map;

// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 		ft_errorv2("Error: map not found");
// 	tmp = NULL;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		tmp = ft_strjoin(tmp, line);
// 		free(line);
// 	}
// 	map = ft_split(tmp, '\n');
// 	return (free(tmp), map);
// }

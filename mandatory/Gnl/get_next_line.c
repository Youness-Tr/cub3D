/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:28:57 by ajabri            #+#    #+#             */
/*   Updated: 2024/09/15 10:07:46 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/get_next_line.h"

char	*ft_remainder(char *save)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!save)
		return (NULL);
	if (save[0] == '\0')
		return (free(save), NULL);
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	if (save[i] == '\0')
		return (free(save), NULL);
	rest = malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!rest)
		return (free(save), NULL);
	i++;
	while (save[i] != '\0')
		rest[j++] = save[i++];
	rest[j] = '\0';
	free(save);
	return (rest);
}

char	*get_linef(char *save)
{
	char	*line;
	size_t	len;
	int		check;

	check = 2;
	len = 0;
	if (!save[len])
		return (NULL);
	while (save[len] && save[len] != '\n')
		len++;
	if (save[len] == '\0')
		check = 1;
	line = malloc(sizeof(char) * (len + check));
	if (!line)
		return (free(save), NULL);
	len = 0;
	while (save[len] && save[len] != '\n')
	{
		line[len] = save[len];
		len++;
	}
	if (check == 2)
		line[len++] = '\n';
	line[len] = '\0';
	return (line);
}

char	*read_f(int fd, char *save)
{
	char	*buffer;
	char	*tmp;
	ssize_t	readed;

	buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (free(save), NULL);
	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
		{
			return (free(buffer), free(save), NULL);
		}
		buffer[readed] = '\0';
		tmp = ft_strdup(save);
		free(save);
		save = ft_strjoin(tmp, buffer);
		// free(tmp); // edit by VENOM
		if (ft_strchr(save, '\n'))
			break ;
	}
	return (free(buffer), save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_f(fd, save);
	if (!save)
		return (NULL);
	line = get_linef(save);
	save = ft_remainder(save);
	return (line);
}

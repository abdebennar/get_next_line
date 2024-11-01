/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:24:20 by abennar           #+#    #+#             */
/*   Updated: 2024/10/27 14:21:32 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*eter_line(char **line)
{
	char	*str;
	char	*r_line;
	int		i;

	if (!line || !*line)
		return (NULL);
	str = *line;
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	r_line = ft_strndup(str, i);
	*line = ft_strndup((str + i), ft_strlen(str + i));
	m_free(str);
	return (r_line);
}

char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	char		*buff;
	ssize_t		r;

	if (fd < 0)
		return (errno = EBADF, NULL);
	if (read(fd, 0, 0) == -1)
		return (m_free(line[fd]), line[fd] = NULL, NULL);
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (m_free(line[fd]), line[fd] = NULL, NULL);
	r = 1;
	while (r > 0)
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (!buff)
			break ;
		buff[r] = '\0';
		line[fd] = ft_strjoin(line[fd], buff);
		if (detect_n(buff))
			break ;
	}
	m_free(buff);
	return (eter_line(&line[fd]));
}

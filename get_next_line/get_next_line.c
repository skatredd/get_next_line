/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatredd <skatredd@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:36:30 by skatredd          #+#    #+#             */
/*   Updated: 2025/04/23 15:04:39 by skatredd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_data(char *data, char *buff)
{
	char	*temp;
	int		len1;
	int		len2;

	if (data)
		len1 = ft_strlen(data);
	else
		len1 = 0;
	len2 = ft_strlen(buff);
	temp = malloc(len1 + len2 + 1);
	if (!temp)
	{
		free(data);
		return (NULL);
	}
	if (data)
		ft_memcpy(temp, data, len1);
	ft_memcpy(temp + len1, buff, len2);
	temp[len1 + len2] = '\0';
	free(data);
	return (temp);
}

char	*read_to_data(int fd, char *data)
{
	char	*buff;
	int		bytes;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (free(data), NULL);
	bytes = 1;
	while (!ft_strchr(data, '\n') && bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buff), free(data), NULL);
		buff[bytes] = '\0';
		data = join_data(data, buff);
		if (!data)
			return (free(buff), NULL);
	}
	free(buff);
	return (data);
}

char	*extract_line(char *data)
{
	int	i;

	if (!data || !data[0])
		return (NULL);
	i = 0;
	while (data[i] && data[i] != '\n')
		i++;
	if (data[i] == '\n')
		i++;
	return (ft_substr(data, 0, i));
}

char	*clean_data(char *data)
{
	int		i;
	char	*left;

	i = 0;
	while (data[i] && data[i] != '\n')
		i++;
	if (!data[i])
		return (free(data), NULL);
	left = ft_substr(data, i + 1, ft_strlen(data + i + 1));
	free(data);
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*data;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	data = read_to_data(fd, data);
	if (!data)
		return (NULL);
	line = extract_line(data);
	if (!line)
	{
		free(data);
		data = NULL;
		return (NULL);
	}
	data = clean_data(data);
	return (line);
}

// #include "get_next_line.h"
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>

// int main(void)
// {
// 	int fd = open("testfile.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("open");
// 		return (1);
// 	}

// 	char *line;
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("LINE: %s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }

// //testfile.txt
// Short
// Line
// Another longer line with more content
// One more line
// This one has no newline at EOF
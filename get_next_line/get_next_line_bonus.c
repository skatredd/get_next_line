/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skatredd <skatredd@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:49:32 by skatredd          #+#    #+#             */
/*   Updated: 2025/04/23 15:04:10 by skatredd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*data[1024];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	data[fd] = read_to_data(fd, data[fd]);
	if (!data[fd])
		return (NULL);
	line = extract_line(data[fd]);
	if (!line)
	{
		free(data[fd]);
		data[fd] = NULL;
		return (NULL);
	}
	data[fd] = clean_data(data[fd]);
	return (line);
}

// #include "get_next_line_bonus.h"
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>

// int main(void)
// {
// 	int fd1 = open("testfile1.txt", O_RDONLY);
// 	int fd2 = open("testfile2.txt", O_RDONLY);

// 	if (fd1 < 0 || fd2 < 0)
// 	{
// 		perror("open");
// 		return (1);
// 	}

// 	char *line1, *line2;
// 	while ((line1 = get_next_line(fd1)) || (line2 = get_next_line(fd2)))
// 	{
// 		if (line1)
// 		{
// 			printf("FD1: %s", line1);
// 			free(line1);
// 		}
// 		if (line2)
// 		{
// 			printf("FD2: %s", line2);
// 			free(line2);
// 		}
// 	}
// 	close(fd1);
// 	close(fd2);
// 	return (0);
// }

// //testfile1.txt
// file1: line1
// file1: line2
// file1: line3

// //testfile2.txt
// file2: lineA
// file2: lineB
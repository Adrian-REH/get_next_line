/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 06:12:12 by adherrer          #+#    #+#             */
/*   Updated: 2024/04/08 21:40:28 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	ft_read_line(char **file, char **line)
{
	int	l_word;

	l_word = 0;
	while ((*file)[l_word])
		if ((*file)[(l_word)++] == '\n')
			break ;
	if (l_word > 0)
	{
		*line = ft_substr(*file, 0, l_word);
		if (!*line)
			return ((void)0);
	}
	else
		*line = 0;
}

static void	ft_delete_first_line(char **file)
{
	char	*value;
	char	*temp;

	temp = 0;
	value = ft_strchr(*file, '\n');
	if (!value)
	{
		free(*file);
		*file = 0;
		return ;
	}
	else if (value[1])
		temp = ft_strdup(++value);
	free(*file);
	*file = temp;
}

static	void	ft_free_strjoin(char **file, char **buffer)
{
	char	*dst;
	size_t	size;
	char	*temp;
	size_t	i;

	size = ft_strlen(*file) + ft_strlen(*buffer) + 1;
	dst = malloc(size);
	i = 0;
	if (!dst)
		return ;
	while ((i + 1) < size && size && (*file)[i])
	{
		dst[i] = ((*file)[i]);
		i++;
	}
	if (size > 0)
		dst[i] = 0;
	ft_strlcat(dst, *buffer, size);
	temp = dst;
	if (!temp)
		return ;
	free(*file);
	*file = temp;
}

static void	ft_read_file(int fd, char **file)
{
	int		by_re;
	char	*buffer;

	if (!file)
		return ;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return ;
	by_re = 1;
	while ((by_re > 0))
	{
		by_re = read(fd, buffer, BUFFER_SIZE);
		if (by_re < 0)
		{
			free(*file);
			*file = 0;
			break ;
		}
		buffer[by_re] = 0;
		ft_free_strjoin(file, &buffer);
		if (ft_strchr(*file, '\n'))
			break ;
	}
	free(buffer);
}

char	*get_next_line(int fd)
{
	static char	*file[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!file[fd])
	{
		file[fd] = malloc(1);
		if (!file[fd])
			return (0);
		*file[fd] = 0;
	}
	ft_read_file(fd, &(file[fd]));
	if (!file[fd])
		return ((char *)0);
	ft_read_line(&(file[fd]), &line);
	ft_delete_first_line(&(file[fd]));
	return (line);
}
/* 

#include <fcntl.h>

void test_inf(int fd, int fd, char *(*f)(int))
{
	int i = 0;
	char *line;

	printf("RESPONSE\n");
	while (1)
	{
		line = f(fd);
		if (!line)
			break ;
		printf("[%d]: %s\n", i, line);
		i++;
		free(line);
	}

}
 int main()
{

	int fd = open("archivo.txt", O_RDONLY);
	int fd2 = open("archivo_2.txt", O_RDONLY);
	test_inf(fd, fd2, get_next_line);
	close(fd);
	close(fd2);


	int fd = open("archivo.txt", O_RDONLY);
	int fd2 = open("archivo_2.txt", O_RDONLY);
	test_inf(fd, fd2, gnl);
	close(fd);
	close(fd2); 
} */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:36:00 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/06 14:28:35 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static int	ft_varlen(char *s, int version)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	if (version == 1)
	{
		while (s[i] != '\0')
			i++;
	}
	if (version == 2)
	{
		while (s[i] != '\0' && s[i] != '\n')
			i++;
		if (s[i] == '\n')
			i++;
	}
	return (i);
}

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;

	s1_len = ft_varlen(s1, 1);
	s2_len = ft_varlen(s2, 2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (str == NULL)
		return (free_ptr((void **)&s1), NULL);
	i = 0;
	while (i < s1_len)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < s2_len)
		str[i++] = s2[j++];
	str[i] = '\0';
	free_ptr((void **)&s1);
	return (str);
}

static void	ft_remainder(char *stash)
{
	int	i;
	int	j;

	if (ft_getnl(stash) == NULL)
		return ;
	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	i++;
	j = 0;
	while (stash[i] != '\0')
	{
		stash[j] = stash[i];
		i++;
		j++;
	}
	stash[j] = '\0';
}

static char	*ft_readfile(int fd, char *stash)
{
	char	*buf;
	int		read_bytes;

	buf = NULL;
	read_bytes = 1;
	while (read_bytes > 0)
	{
		buf = ft_strjoin_gnl(buf, stash);
		if (buf == NULL)
			return (NULL);
		if (ft_getnl(stash) != NULL)
			return (buf);
		read_bytes = read(fd, stash, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			stash[0] = '\0';
			free_ptr((void **)&buf);
			return (NULL);
		}
		stash[read_bytes] = '\0';
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	stash[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_readfile(fd, stash);
	if (line == NULL || ft_varlen(line, 1) == 0)
	{
		free_ptr((void **)&line);
		return (NULL);
	}
	ft_remainder(stash);
	return (line);
}

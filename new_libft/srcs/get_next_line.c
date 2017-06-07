/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhakh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 18:53:09 by rhakh             #+#    #+#             */
/*   Updated: 2016/12/28 18:53:10 by rhakh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_realloc(t_t *t)
{
	char			*new_str;
	size_t			new_size;

	new_size = t->last_size * 2;
	if ((new_str = ft_strnew(new_size)) == NULL)
		return (0);
	ft_strncpy(new_str, t->line, t->last_size);
	free(t->line);
	t->line = new_str;
	t->last_size *= 2;
	return (1);
}

static t_t			*ft_push_new_back(int fd)
{
	t_t				*n_t;

	if ((n_t = (t_t *)malloc(sizeof(t_t))) == NULL)
		return (NULL);
	else
	{
		if ((n_t->line = ft_strnew(BUFF_SIZE)))
		{
			n_t->i = 0;
			n_t->last_size = BUFF_SIZE;
			n_t->next_line = 0;
			n_t->fd = fd;
			n_t->next = NULL;
			return (n_t);
		}
		else
			return (NULL);
	}
}

static int			ft_return_line(t_t *t, char **line)
{
	size_t			i;
	char			*tmp;

	i = 0;
	while ((t->line)[i] != '\n' && (t->line)[i] != '\0')
		i++;
	if ((*line = ft_strnew(i)) == NULL)
		return (-1);
	ft_strncpy(*line, t->line, i);
	if ((tmp = ft_strnew(t->last_size * 2)) == NULL)
		return (-1);
	ft_strcpy(tmp, t->line + i + 1);
	ft_strdel(&(t->line));
	t->line = tmp;
	t->i = ft_strlen(t->line);
	return (1);
}

static int			ft_read_line(const int fd, t_t *t, char **line)
{
	int				b;
	char			buff[BUFF_SIZE + 1];

	ft_bzero(buff, BUFF_SIZE + 1);
	while (!ft_strchr(t->line, '\n') && ((b = read(fd, buff, BUFF_SIZE)) > 0))
	{
		if (t->i + b >= t->last_size)
			if ((ft_realloc(t)) == 0)
				return (-1);
		ft_strncpy(t->line + t->i, buff, b);
		t->i += b;
		if (ft_strchr(t->line, '\n'))
		{
			if (ft_return_line(t, line) == 1)
				return (1);
			else
				return (-1);
		}
		ft_bzero(buff, BUFF_SIZE);
	}
	if ((b == 0) && (ft_strlen(t->line + t->next_line) == 0) &&
			(*line = ft_strdup("")))
		return (0);
	else
		return (ft_return_line(t, line));
}

int					get_next_line(const int fd, char **line)
{
	static t_t		*t;
	int				res;
	t_t				*current;

	res = 0;
	if (line == NULL)
		return (-1);
	if (t == NULL)
		if ((t = ft_push_new_back(fd)) == NULL)
			res = -1;
	current = t;
	if (read(fd, 0, 0) == -1 || fd < 0 || BUFF_SIZE < 0 || BUFF_SIZE > 65535)
		res = -1;
	while (current && res != -1)
	{
		if (current->fd == fd)
			return (ft_read_line(fd, current, line));
		if (current->next == NULL &&
			((current->next = ft_push_new_back(fd)) != NULL))
			return (ft_read_line(fd, (current->next), line));
		current = current->next;
	}
	if (res == -1)
		*line = ft_strdup("");
	return (-1);
}

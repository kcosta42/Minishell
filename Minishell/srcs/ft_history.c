/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:59:39 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/22 11:00:25 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_keys.h"
#include "ft_singletons.h"
#include "ft_history.h"

t_list		*ft_initialise_history(void)
{
	t_list		*history;
	char		*line;
	int			fd;
	char		*path;

	history = NULL;
	path = ft_strjoin(*ft_get_home(), "/.0sh_history");
	if ((fd = open(path, O_RDONLY | O_CREAT)) == -1)
		return (NULL);
	chmod(path, 0644);
	while (ft_getline(fd, &line) > 0)
	{
		ft_lstadd(&history, ft_lstnew(line, ft_strlen(line) + 1));
		ft_strdel(&line);
	}
	ft_strdel(&line);
	ft_strdel(&path);
	if (close(fd) == -1)
		return (NULL);
	return (history);
}

static int	ft_history_handler(t_list *history, char next)
{
	static int	current = 0;
	int			index;
	char		**input;

	index = 0;
	current = (history) ? current : 0;
	if (!history)
		return (1);
	input = ft_get_input();
	while (history && index++ < current - 2 * (!next))
		history = history->next;
	if (history)
		current = (next) ? current + 1 : current - 1;
	current = (current < 0) ? 0 : current;
	if (history || !next)
		ft_strdel(input);
	if (!next && !current)
		*input = ft_strnew(0);
	else if (history)
		*input = ft_strdup(history->content);
	if (!history)
		return (ft_printf("\a"));
	return (0);
}

int			ft_add_history(char *entry)
{
	t_list		**history;
	int			fd;
	char		*path;

	history = ft_get_history();
	ft_history_handler(NULL, 0);
	if (*history && !ft_strcmp((*history)->content, entry))
		return (0);
	path = ft_strjoin(*ft_get_home(), "/.0sh_history");
	if ((fd = open(path, O_WRONLY | O_APPEND)) == -1)
		return (-1);
	if (*entry)
	{
		write(fd, entry, ft_strlen(entry));
		write(fd, "\n", 1);
	}
	ft_lstadd(history, ft_lstnew(entry, ft_strlen(entry) + 1));
	ft_strdel(&path);
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int			ft_seek_history(char next, size_t *col)
{
	t_list		*history;
	int			i;
	size_t		size;

	i = 0;
	size = ft_strlen(*ft_get_input());
	ft_printf("\033[%dD", (*col) ? *col : -1);
	while (i++ < (int)size)
		ft_putchar(' ');
	*col = size;
	history = *ft_get_history();
	ft_history_handler(history, next);
	ft_show_input(col);
	*col = ft_strlen(*ft_get_input());
	return (0);
}

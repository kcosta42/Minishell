/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 15:57:27 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/11 10:15:14 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_shell.h"

static size_t	ft_count_commands(const char *line)
{
	size_t		count;

	count = 0;
	while (*line)
	{
		while (*line && ft_isblank(*line))
			line++;
		if (*line)
			count++;
		if (*line == '"')
		{
			line++;
			while (*line && *line != '"')
				line++;
			line++;
		}
		else
			while (*line && !ft_isblank(*line))
				line++;
	}
	return (count);
}

static size_t	ft_get_quote(char **str, const char *line)
{
	size_t		length;

	length = 0;
	line++;
	while (line[length] && line[length] != '"')
		length++;
	*str = ft_strsub(line, 0, length);
	return (length + 2);
}

static size_t	ft_get_sub(char **str, const char *line)
{
	size_t		length;

	length = 0;
	while (line[length] && !ft_isblank(line[length]))
		length++;
	*str = ft_strsub(line, 0, length);
	return (length);
}

char			**ft_get_commands(const char *line)
{
	char		**commands;
	size_t		index;
	size_t		size;

	if (!line)
		return (NULL);
	size = ft_count_commands(line) + 1;
	if (!(commands = (char**)ft_memalloc(sizeof(char*) * size)))
		return (NULL);
	index = 0;
	while (index < size - 1)
	{
		while (*line && ft_isblank(*line))
			line++;
		if (*line == '"')
			line += ft_get_quote(&(commands[index]), line);
		else
			line += ft_get_sub(&(commands[index]), line);
		index++;
	}
	return (commands);
}

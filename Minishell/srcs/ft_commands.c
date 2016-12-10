/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 15:57:27 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/10 17:38:24 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_shell.h"

size_t	ft_count_commands(const char *line)
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
			while (*line && *line != '"')
				line++;
		else
			while (*line && !ft_isblank(*line))
				line++;
	}
	return (count);
}
/*
static int		ft_get_quote(char **str, const char *line)
{
	size_t		length;

	length = 0;
	while (line[length] && line[length] != '"')
		length++;
	*str = ft_strsub(line, 1, length - 2);
	ft_printf("%s\n", *str);
	return (length + 1);
}

static int		ft_get_sub(char **str, const char *line)
{
	size_t		length;

	length = 0;
	while (line[length] && !ft_isblank(line[length]))
		length++;
	*str = ft_strsub(line, 0, length);
	ft_printf("%s\n", *str);
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
	ft_printf("%d\n", size);
	commands = (char**)ft_memalloc(sizeof(char*) * size);
	index = 0;
	while (index < size)
	{
		while (*line && ft_isblank(*line))
			line++;
		if (*line == '"')
			line += ft_get_quote(&(commands[index]), line);
		else
			line += ft_get_sub(&(commands[index]), line);
		index++;
	}
	commands[index] = NULL;
	int e = 0;
	while (commands[e])
		ft_printf("%s\n", commands[e++]);
	ft_printf("hola\n");
	return (commands);
}*/
static int	ft_wcount(const char *s)
{
	int		wcount;

	wcount = 0;
	while (*s)
	{
		while (*s && ft_isblank(*s))
			s++;
		if (*s)
			wcount++;
		if (*s == '"')
		{
			s++;
			while (*s && *s != '"')
				s++;
			if (*s)
				s++;
		}
		else
			while (*s && !ft_isblank(*s))
				s++;
	}
	return (wcount);
}

char		**ft_get_commands(const char *s)
{
	char	**split;
	int		words;
	int		index;
	int		length;

	if (!s)
		return (NULL);
	index = 0;
	words = ft_wcount(s) + 1;
	ft_printf("%d\n", words);
	if (!(split = (char**)ft_memalloc(sizeof(char*) * words)))
		return (NULL);
	while (index < words - 1)
	{
		length = 0;
		while (*s && ft_isblank(*s))
			s++;
		if (*s == '"')
		{
			s++;
			while (s[length] && s[length] != '"')
				length++;
			split[index] = ft_strsub(s, 0, length - 1);
			s++;
		}
		else
		{
			while (s[length] && !ft_isblank(s[length]))
				length++;
			split[index] = ft_strsub(s, 0, length);
		}
		index++;
		s += length;
	}
	split[index] = 0;
	int e = 0;
	ft_printf("---------\n");
	while (split[e])
		ft_printf("%s\n", split[e++]);
	ft_printf("---------\n");
	return (split);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 19:09:47 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/14 19:52:44 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_keys.h"

static int		ft_match(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	if (*s1 == 0 && *s2 == 0)
		return (1);
	else if (*s2 == '*')
	{
		if (*s1 == 0)
			return ft_match(s1, s2 + 1);
		else
			return (ft_match(s1 + 1, s2) || ft_match(s1, s2 + 1));
	}
	else
	{
		if (*s1 == *s2)
			return ft_match(s1 + 1, s2 + 1);
		else
			return (0);
	}
	return (0);
}

static char		*ft_get_name(const char *name, size_t len)
{
	char	*new;

	new = ft_strnew(len);
	return (ft_strncpy(new, name, len));
}

static char		*ft_com_dir(char **envp, const char *current)
{
	DIR				*dirp;
	struct dirent	*entry;
	char			*wannabe;

	(void)envp;
	if (!(dirp = opendir(".")))
		return (NULL);
	entry = readdir(dirp);
	wannabe = NULL;
	while (ft_match(wannabe, (char*)current) != 1)
	{
		if (wannabe)
			ft_strdel(&wannabe);
		if (!(entry = readdir(dirp)))
			break ;
		wannabe = ft_get_name(entry->d_name, entry->d_namlen);
	}
	if (closedir(dirp) == -1)
		return (NULL);
	return (wannabe);
}

char		*ft_com_path(char **envp, const char *current)
{
	DIR				*dirp;
	struct dirent	*entry;
	char			*wannabe;
	
	(void)envp;
	if (!(dirp = opendir(".")))
		return (NULL);
	entry = readdir(dirp);
	wannabe = NULL;
	while (ft_match(wannabe, (char*)current) != 1)
	{
		if (wannabe)
			ft_strdel(&wannabe);
		if (!(entry = readdir(dirp)))
			break ;
		wannabe = ft_get_name(entry->d_name, entry->d_namlen);
	}
	if (closedir(dirp) == -1)
		return (NULL);
	return (wannabe);
}

int				ft_completion(char **envp, size_t *col)
{
	char	**input;
	char	*current;
	char	*wannabe;

	(void)envp;
	current = ft_strjoin(*ft_get_input(), "*");
	input = ft_get_input();
	wannabe = ft_com_dir(envp, current);
	*input = (wannabe) ? wannabe : *input;
	ft_show_input(col);
	*col = ft_strlen(*input);
	ft_strdel(&current);
	return (0);
}

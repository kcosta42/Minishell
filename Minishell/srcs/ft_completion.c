/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 19:09:47 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/17 12:01:26 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_keys.h"
#include "ft_singletons.h"

int				ft_match(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	if (*s1 == 0 && *s2 == 0)
		return (1);
	else if (*s2 == '*')
	{
		if (*s1 == 0)
			return (ft_match(s1, s2 + 1));
		else
			return (ft_match(s1 + 1, s2) || ft_match(s1, s2 + 1));
	}
	else
	{
		if (*s1 == *s2)
			return (ft_match(s1 + 1, s2 + 1));
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

char			*ft_find_match(const char *dir, const char *current)
{
	DIR				*dirp;
	struct dirent	*entry;
	char			*wannabe;

	if (!(dirp = opendir(dir)))
		return (NULL);
	wannabe = NULL;
	while (ft_match(wannabe, (char*)current) != 1)
	{
		if (wannabe)
			ft_strdel(&wannabe);
		if (!(entry = readdir(dirp)))
			break ;
		if (entry->d_name[0] != '.')
			wannabe = ft_get_name(entry->d_name, entry->d_namlen);
	}
	if (closedir(dirp) == -1)
		return (NULL);
	return (wannabe);
}

static int		ft_com_update(char *wannabe)
{
	char	**input;
	char	*tmp;
	char	*new;

	if (!wannabe)
		return (-1);
	input = ft_get_input();
	if (ft_strrchr(*input, ' '))
	{
		tmp = ft_strnew(ft_strrchr(*input, ' ') - *input + 1);
		tmp = ft_strncpy(tmp, *input, ft_strrchr(*input, ' ') - *input + 1);
		new = ft_strjoin(tmp, wannabe);
		ft_strdel(&tmp);
		ft_strdel(input);
		ft_strdel(&wannabe);
		*input = new;
		return (0);
	}
	ft_strdel(input);
	*input = wannabe;
	return (1);
}

int				ft_completion(char **envp, size_t *col)
{
	char	*tmp;
	char	*current;
	char	*wannabe;

	tmp = (!ft_strrchr(*ft_get_input(), ' ')) ? *ft_get_input() :
										ft_strrchr(*ft_get_input(), ' ') + 1;
	current = ft_strjoin(tmp, "*");
	if (!ft_strcmp(current, "*"))
		return (1);
	if (ft_strrchr(*ft_get_input(), ' '))
		wannabe = ft_com_dir(current);
	else if (!(wannabe = ft_com_builtins(current)))
		if (!(wannabe = ft_com_path(envp, current)))
			wannabe = ft_com_dir(current);
	ft_com_update(wannabe);
	ft_show_input(col);
	*col = ft_strlen(*ft_get_input());
	ft_strdel(&current);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 18:28:25 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/10 09:08:44 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_shell.h"

void		ft_tabdel(char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i])
	{
		ft_strdel(&((*tab)[i]));
		i++;
	}
	ft_strdel((char**)tab);
}

int			ft_tabreplace(char ***tab, char *to_find, char *entry)
{
	char	**tmp;
	char	**result;

	result = ft_tabstr(*tab, to_find);
	if (result)
		**result = 0;
	tmp = *tab;
	*tab = ft_tabdup(*tab, entry);
	ft_tabdel(&tmp);
	return (0);
}

char		**ft_tabstr(char **tab, char *entry)
{
	while (*tab)
	{
		if (!ft_strncmp(*tab, entry, ft_strlen(entry)))
			return (tab);
		tab++;
	}
	return (NULL);
}

size_t		ft_tablen(char **tab)
{
	size_t	size;
	size_t	index;

	size = 0;
	index = 0;
	while (tab[index])
	{
		if (*tab[index])
			size++;
		index++;
	}
	return (size);
}

char		**ft_tabdup(char **tab, char *entry)
{
	char	**new;
	size_t	size;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	size = ft_tablen(tab) + 1 + (entry != NULL);
	if (!(new = (char**)ft_memalloc(sizeof(char*) * size)))
		return (NULL);
	while (tab[++i])
	{
		if (*tab[i])
			new[j++] = ft_strdup(tab[i]);
		else if (entry)
		{
			new[j++] = ft_strdup(entry);
			ft_strdel(&entry);
		}
	}
	if (entry)
		new[j++] = ft_strdup(entry);
	return (new);
}

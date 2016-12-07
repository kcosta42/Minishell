/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 18:28:25 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/07 19:32:28 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_shell.h"

void		ft_tabdel(char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i])
		ft_strdel(&((*tab)[i++]));
	//ft_strdel((char**)*tab);
}

size_t		ft_tablen(char **tab)
{
	size_t	size;

	size = 0;
	while (tab[size])
		size++;
	return (size);
}

char		**ft_tabdup(char **tab, char *entry)
{
	char	**new;
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_tablen(tab) + 1 + (entry != NULL);
	if (!(new = (char**)ft_memalloc(sizeof(char*) * size)))
		return (NULL);
	while (tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	if (entry)
		new[i] = ft_strdup(entry);
	return (new);
}

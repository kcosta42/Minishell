/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 16:34:58 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/14 19:19:58 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_keys.h"

char	**ft_get_input(void)
{
	static char	*input = NULL;

	if (input == NULL)
		input = ft_strnew(0);
	return (&input);
}

int		ft_add_input(char c, size_t *col)
{
	ft_printf("\033[%dD", (*col) ? *col : -1);
	ft_strinsert(ft_get_input(), c, *col);
	(*col)++;
	ft_printf("%s", *ft_get_input());
	ft_printf("\033[%dD", ft_strlen(*ft_get_input()));
	ft_printf("\033[%dC", (*col) ? *col : -1);
	return (0);
}

int		ft_show_input(size_t *col)
{
	ft_printf("\033[%dD", (*col) ? *col : -1);
	ft_printf("%s", *ft_get_input());
	return (0);
}

int		ft_remove_input(size_t *col)
{
	size_t	size;

	size = ft_strlen(*ft_get_input());
	ft_printf("\033[%dD", (*col) ? *col : -1);
	for (int i = 0; i < (int)size + (*col == 1); i++)
		ft_putchar(' ');
	ft_printf("\033[%dD", size + (*col == 1));
	ft_strremove(ft_get_input(), *col);
	ft_printf("%s", *ft_get_input());
	(*col)--;
	size = ft_strlen(*ft_get_input());
	ft_printf("\033[%dD", (size) ? size : -1);
	ft_printf("\033[%dC", (*col) ? *col : -1);
	return (0);
}

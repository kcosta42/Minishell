/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_arrows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:22:59 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/15 17:45:58 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_keys.h"
#include "ft_singletons.h"
#include "ft_history.h"

int		ft_key_up(char **envp, size_t *col)
{
	(void)envp;
	ft_seek_history(1, col);
	return (1);
}

int		ft_key_down(char **envp, size_t *col)
{
	(void)envp;
	ft_seek_history(0, col);
	return (1);
}

int		ft_key_right(char **envp, size_t *col)
{
	(void)envp;
	if (*col < ft_strlen(*ft_get_input()))
	{
		(*col)++;
		ft_printf("\033[1C");
	}
	return (1);
}

int		ft_key_left(char **envp, size_t *col)
{
	(void)envp;
	if (*col > 0)
	{
		ft_printf("\033[1D");
		(*col)--;
	}
	return (1);
}

int		ft_key_isarrow(char key)
{
	if (key == '\x1b')
	{
		read(0, &key, 1);
		if (key == '\x5b')
		{
			read(0, &key, 1);
			if (key == '\x41')
				return (K_UP);
			if (key == '\x42')
				return (K_DOWN);
			if (key == '\x43')
				return (K_RIGHT);
			if (key == '\x44')
				return (K_LEFT);
		}
	}
	return (K_NONE);
}

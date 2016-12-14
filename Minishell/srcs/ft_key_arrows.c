/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_arrows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:22:59 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/14 17:21:33 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_keys.h"

static char		ft_key_isup(char key)
{
	return (key == '\x41');
}

static char		ft_key_isdown(char key)
{
	return (key == '\x42');
}

static char		ft_key_isright(char key)
{
	return (key == '\x43');
}

static char		ft_key_isleft(char key)
{
	return (key == '\x44');
}

int				ft_key_isarrow(char key)
{
	if (key == '\x1b')
	{
		read(0, &key, 1);
		if (key == '\x5b')
		{
			read(0, &key, 1);
			if (ft_key_isup(key))
				return (K_UP);
			if (ft_key_isdown(key))
				return (K_DOWN);
			if (ft_key_isright(key))
				return (K_RIGHT);
			if (ft_key_isleft(key))
				return (K_LEFT);
		}
	}
	return (K_NONE);
}

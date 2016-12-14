/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:23:54 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/14 17:21:29 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_keys.h"

static char		ft_key_isback(char key)
{
	return (key == '\x7f');
}

static char		ft_key_istab(char key)
{
	return (key == '\x9');
}

static char		ft_key_isreturn(char key)
{
	return (key == '\xa');
}

static char		ft_key_isctrl_d(char key)
{
	return (key == '\x4');
}

int				ft_key_iscontrol(char key)
{
	if (ft_key_isback(key))
		return (K_BACK);
	if (ft_key_istab(key))
		return (K_TAB);
	if (ft_key_isreturn(key))
		return (K_RETURN);
	if (ft_key_isctrl_d(key))
		return (K_CTRL_D);
	return (K_NONE);
}

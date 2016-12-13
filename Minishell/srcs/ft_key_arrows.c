/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_arrows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:22:59 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/13 11:54:07 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_keys.h"

char		ft_key_isup(const char *pressed)
{
	const char	*key = "\x1b\x5b\x41\0\0\0";

	if (!memcmp((void*)key, (void*)pressed, MAX_LENGTH))
		return (1);
	return (0);
}

char		ft_key_isdown(const char *pressed)
{
	const char	*key = "\x1b\x5b\x42\0\0\0";

	if (!memcmp((void*)key, (void*)pressed, MAX_LENGTH))
		return (1);
	return (0);
}

char		ft_key_isright(const char *pressed)
{
	const char	*key = "\x1b\x5b\x43\0\0\0";

	if (!memcmp((void*)key, (void*)pressed, MAX_LENGTH))
		return (1);
	return (0);
}

char		ft_key_isleft(const char *pressed)
{
	const char	*key = "\x1b\x5b\x44\0\0\0";

	if (!memcmp((void*)key, (void*)pressed, MAX_LENGTH))
		return (1);
	return (0);
}

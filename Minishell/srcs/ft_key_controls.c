/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:23:54 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/13 16:10:18 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_keys.h"

char		ft_key_isreturn(const char *pressed)
{
	const char	*key = "\x7f\0\0\0\0\0";

	if (!memcmp((void*)key, (void*)pressed, MAX_LENGTH))
		return (1);
	return (0);
}

char		ft_key_istab(const char *pressed)
{
	const char	*key = "\x9\0\0\0\0\0";

	if (!memcmp((void*)key, (void*)pressed, MAX_LENGTH))
		return (1);
	return (0);
}

char		ft_key_isenter(const char *pressed)
{
	const char	*key = "\xa\0\0\0\0\0";

	if (!memcmp((void*)key, (void*)pressed, MAX_LENGTH))
		return (1);
	return (0);
}

char		ft_key_isctrl_d(const char *pressed)
{
	const char	*key = "\x4\0\0\0\0\0";

	if (!memcmp((void*)key, (void*)pressed, MAX_LENGTH))
		return (1);
	return (0);
}

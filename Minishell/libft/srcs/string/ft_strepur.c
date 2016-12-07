/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strepur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 14:30:27 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/07 14:43:18 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_ctype.h"

char	*ft_strepur(const char *str)
{
	char	*ret;
	char	*epur;

	epur = ft_strnew(ft_strlen(str));
	ret = epur;
	while (*str && ft_isblank(*str))
		str++;
	while (*str)
	{
		while (*str && !ft_isblank(*str))
			*epur++ = *str++;
		while (ft_isblank(*str))
			str++;
		if (*str)
			*epur++ = ' ';
	}
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:18:52 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/12 19:25:36 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_KEYS_H
# define FT_KEYS_H

# ifndef MAX_LENGTH
#  define MAX_LENGTH 6
# endif

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <termios.h>

# include <sys/ioctl.h>

# include "libft.h"

char		ft_key_istab(const char *pressed);
char		ft_key_isenter(const char *pressed);
char		ft_key_isctrl_d(const char *pressed);
char		ft_key_isup(const char *pressed);
char		ft_key_isdown(const char *pressed);
char		ft_key_isright(const char *pressed);
char		ft_key_isleft(const char *pressed);

#endif

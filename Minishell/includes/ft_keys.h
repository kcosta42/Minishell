/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:18:52 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/14 19:38:20 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_KEYS_H
# define FT_KEYS_H

# ifndef KEYS
#  define KEYS

#  define K_CTRL_D		(-1)
#  define K_NONE		0
#  define K_RETURN		1
#  define K_TAB			2
#  define K_BACK		3
#  define K_UP			4
#  define K_DOWN		5
#  define K_LEFT		6
#  define K_RIGHT		7

# endif

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <dirent.h>
# include <termios.h>

# include <sys/dir.h>
# include <sys/ioctl.h>

# include "libft.h"

void		ft_default_mode(void);
int			ft_completion(char **envp, size_t *col);

int			ft_key_iscontrol(char key);
int			ft_key_isarrow(char key);

char		**ft_get_input(void);
int			ft_add_input(char c, size_t *col);
int			ft_remove_input(size_t *col);
int			ft_show_input(size_t *col);

#endif

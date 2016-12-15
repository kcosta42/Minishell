/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:18:52 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/15 17:16:48 by kcosta           ###   ########.fr       */
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
# include <fcntl.h>
# include <dirent.h>
# include <termios.h>

# include <sys/dir.h>
# include <sys/ioctl.h>

# include "libft.h"

typedef struct	s_keys
{
	int			key;
	int			(*func)(char **, size_t *);
}				t_keys;

int				ft_key_up(char **envp, size_t *col);
int				ft_key_down(char **envp, size_t *col);
int				ft_key_right(char **envp, size_t *col);
int				ft_key_left(char **envp, size_t *col);
int				ft_key_back(char **envp, size_t *col);
int				ft_key_tab(char **envp, size_t *col);
int				ft_key_return(char **envp, size_t *col);
int				ft_key_ctrl_d(char **envp, size_t *col);

void			ft_default_mode(void);

int				ft_match(char *s1, char *s2);
char			*ft_find_match(const char *dir, const char *current);

int				ft_completion(char **envp, size_t *col);
char			*ft_com_builtins(const char *current);
char			*ft_com_path(char **envp, const char *current);
char			*ft_com_dir(const char *current);

int				ft_key_iscontrol(char key);
int				ft_key_isarrow(char key);

int				ft_add_input(char c, size_t *col);
int				ft_remove_input(size_t *col);
int				ft_show_input(size_t *col);

#endif

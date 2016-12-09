/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 16:17:30 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/09 22:08:42 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_H
# define FT_SHELL_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>

# include "libft.h"

typedef void	(*sig_t)(int);

int		ft_builtins(const char *path, char **argv, char ***envp);

int		ft_env(char **argv, char **envp);
int		ft_setenv(char **argv, char ***envp);
int		ft_unsetenv(char **argv, char ***envp);

int		ft_cd(char **argv, char ***envp, int init);
int		ft_cd_initialise(char **pwd, char **old_pwd, char **envp);
int		ft_set_pwd(char ***envp, char *pwd, char *old_pwd);
char	*ft_get_path(char **path);

size_t	ft_tablen(char **tab);
char	**ft_tabdup(char **tab, char *entry);
char	**ft_tabstr(char **tab, char *entry);
void	ft_tabdel(char ***tab);
int		ft_tabreplace(char ***tab, char *to_find, char *entry);

#endif

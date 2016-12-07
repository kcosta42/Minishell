/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 16:17:30 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/07 19:02:01 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_H
# define FT_SHELL_H

# include <fcntl.h>
# include <signal.h>

# include "libft.h"

int		ft_builtins(const char *path, char **argv, char ***envp);
int		ft_env(char **argv, char **envp);
int		ft_setenv(char **argv, char ***envp);
int		ft_unsetenv(char **argv, char ***envp);

size_t	ft_tablen(char **tab);
char	**ft_tabdup(char **tab, char *entry);
void	ft_tabdel(char ***tab);

#endif

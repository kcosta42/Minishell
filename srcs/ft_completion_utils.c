/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:24:43 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/15 14:52:11 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_keys.h"
#include "ft_shell.h"

char		*ft_com_builtins(const char *current)
{
	if (ft_match("echo", (char*)current))
		return (ft_strdup("echo"));
	else if (ft_match("cd", (char*)current))
		return (ft_strdup("cd"));
	else if (ft_match("setenv", (char*)current))
		return (ft_strdup("setenv"));
	else if (ft_match("unsetenv", (char*)current))
		return (ft_strdup("unsetenv"));
	else if (ft_match("env", (char*)current))
		return (ft_strdup("env"));
	else if (ft_match("exit", (char*)current))
		return (ft_strdup("exit"));
	return (NULL);
}

char		*ft_com_path(char **envp, const char *current)
{
	char	*wannabe;
	char	**path;
	int		i;

	path = ft_strsplit(*ft_tabstr(envp, "PATH="), ':');
	path[0] = ft_strstr(path[0], "=") + 1;
	wannabe = NULL;
	i = 0;
	while (!wannabe && path[i])
		wannabe = ft_find_match(path[i++], current);
	path[0] = path[0] - 5;
	ft_tabdel(&path);
	return (wannabe);
}

char		*ft_com_dir(const char *current)
{
	char			*wannabe;
	char			**path;
	char			*t_current;
	char			*absolute_path;
	char			*tmp;

	path = ft_strsplit(current, '/');
	t_current = path[ft_tablen(path) - 1];
	absolute_path = NULL;
	if (ft_strrchr(current, '/'))
	{
		absolute_path = ft_strnew(ft_strrchr(current, '/') - current + 1);
		absolute_path = ft_strncpy(absolute_path, current,
									ft_strrchr(current, '/') - current + 1);
	}
	wannabe = ft_find_match((absolute_path) ? absolute_path : ".", t_current);
	if (absolute_path)
	{
		tmp = wannabe;
		wannabe = ft_strjoin(absolute_path, tmp);
		ft_strdel(&tmp);
		ft_strdel(&absolute_path);
	}
	ft_tabdel(&path);
	return (wannabe);
}

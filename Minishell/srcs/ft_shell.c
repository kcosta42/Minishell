/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 12:43:07 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/22 16:08:29 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_shell.h"
#include "ft_keys.h"
#include "ft_singletons.h"
#include "ft_history.h"

int		g_reset;
pid_t	g_process;

static void		ft_display_prompt(char **envp)
{
	static char	*pwd = NULL;
	char		**tmp;
	char		**path;
	int			size;

	if (envp && (tmp = ft_tabstr(envp, "PWD=")))
	{
		if (pwd)
			ft_strdel(&pwd);
		pwd = ft_strdup(*tmp + 4);
	}
	path = ft_path_split(pwd);
	size = ft_tablen(path) - 1;
	ft_printf("\n\033[1;34m");
	if (size >= 2 && ft_strcmp(path[size - 2], "/"))
		ft_printf("%s/", path[size - 2]);
	if (size >= 1 && ft_strcmp(path[size - 1], "/"))
		ft_printf("%s/", path[size - 1]);
	ft_printf("%s", path[size]);
	ft_printf("\033[0m\n%C ", L'▶');
	ft_tabdel(&path);
	ft_raw_mode();
}

static int		ft_find_command(char *command, char **argv, char **envp)
{
	char	*tmp;
	char	*new;
	char	**paths;
	int		i;

	i = 0;
	execve(command, argv, envp);
	paths = ft_strsplit(*ft_tabstr(envp, "PATH="), ':');
	paths[0] = ft_strstr(paths[0], "=") + 1;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		new = ft_strjoin(tmp, command);
		if (!access(new, F_OK))
			if (access(new, X_OK) == -1)
				return (ft_printf("%s: Permission denied.\n", command));
		execve(new, argv, envp);
		ft_strdel(&tmp);
		ft_strdel(&new);
		i++;
	}
	paths[0] = paths[0] - 5;
	ft_tabdel(&paths);
	return (0);
}

static void		sig_handler(int signal)
{
	char		**input;

	(void)signal;
	ft_default_mode();
	input = ft_get_input();
	ft_strdel(input);
	g_reset = 1;
	if (g_process != 0)
	{
		kill(g_process, SIGKILL);
		ft_putchar('\n');
		return ;
	}
	ft_display_prompt(NULL);
}

static void		ft_command_handler(char **argv, char ***envp)
{
	char	**multi;
	int		index;

	index = 0;
	multi = ft_strsplit(*ft_get_input(), ';');
	while (multi[index])
	{
		argv = ft_get_commands(multi[index++]);
		if (ft_builtins(argv[0], argv, envp))
		{
			g_process = fork();
			if (!g_process)
			{
				if (!ft_find_command(argv[0], argv, *envp))
					ft_printf("0sh: Command not found: %s\n", argv[0]);
			}
			if (g_process > 0)
				wait(NULL);
			if (!g_process)
				exit(1);
		}
		ft_tabdel(&argv);
	}
	ft_tabdel(&multi);
	ft_strdel(ft_get_input());
}

int				main(int argc, char **argv, char **envp)
{
	size_t	col;

	argc = 1;
	g_reset = 0;
	envp = ft_tabdup(envp, NULL);
	ft_cd(argv, &envp, 1);
	signal(SIGINT, sig_handler);
	while (42)
	{
		g_process = 0;
		if (argc == -1)
			exit(1);
		col = 0;
		if (!g_reset)
			ft_display_prompt(envp);
		g_reset = 0;
		while ((argc = ft_check_input(envp, &col)) > 0)
			;
		if (argc == -2)
			continue ;
		ft_add_history(*ft_get_input());
		ft_command_handler(argv, &envp);
	}
	return (0);
}

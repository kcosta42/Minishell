/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_singletons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:46:17 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/15 18:08:40 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_singletons.h"
#include "ft_history.h"

char	**ft_get_input(void)
{
	static char	*input = NULL;

	if (input == NULL)
		input = ft_strnew(0);
	return (&input);
}

char	**ft_get_home(void)
{
	static char *home = NULL;

	return (&home);
}

t_list	**ft_get_history(void)
{
	static t_list *history = NULL;

	if (history == NULL)
		history = ft_initialise_history();
	return (&history);
}
